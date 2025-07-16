/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/16 19:10:22 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


size_t get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
int check_eating(t_philo *philos)
{
    pthread_mutex_lock(philos->flag_mutex);
    if (*philos->stop)
    {
        pthread_mutex_unlock(philos->flag_mutex);
        return 0;
    }
    pthread_mutex_unlock(philos->flag_mutex);
    if (philos->id % 2 == 0) 
    {
        pthread_mutex_lock(philos->right_fork);
         pthread_mutex_lock(philos->flag_mutex);
        if (*philos->stop) 
        {
            pthread_mutex_unlock(philos->flag_mutex);
            pthread_mutex_unlock(philos->right_fork);
            return 0;
        }
        pthread_mutex_unlock(philos->flag_mutex);
        printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
        pthread_mutex_lock(philos->left_fork);
        pthread_mutex_lock(philos->flag_mutex);
        if (*philos->stop) 
        {
            pthread_mutex_unlock(philos->left_fork);
            pthread_mutex_unlock(philos->right_fork);
            pthread_mutex_unlock(philos->flag_mutex);
            return 0;
        }
        pthread_mutex_unlock(philos->flag_mutex);
        printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
    } 
    else 
    {
        pthread_mutex_lock(philos->left_fork);
        pthread_mutex_lock(philos->flag_mutex);
        if (*philos->stop) 
        {
            pthread_mutex_unlock(philos->flag_mutex);
            pthread_mutex_unlock(philos->left_fork);
            return 0;
        }
        pthread_mutex_unlock(philos->flag_mutex);
        printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());

        pthread_mutex_lock(philos->right_fork);
        pthread_mutex_lock(philos->flag_mutex);
        if (*philos->stop)
        {
            pthread_mutex_unlock(philos->right_fork);
            pthread_mutex_unlock(philos->left_fork);
            pthread_mutex_unlock(philos->flag_mutex);
            return 0;
        }
        pthread_mutex_unlock(philos->flag_mutex);
        printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
    }
    return 1;
}

int monitor_death(t_data *data)
{
    int i;
    int all_ate;
    size_t new;
    while (1)
    {
        i = 0;
        all_ate = 1;
        new = get_time_in_ms();
        
        while (i < data->philo_num)
        {
            // Lock last_meal
            pthread_mutex_lock(&data->philos[i].last_meal);
            if (data->death_time < (new - data->philos[i].last_meal_time))
            {
                // Unlock last_meal 
                pthread_mutex_unlock(&data->philos[i].last_meal);
                
                pthread_mutex_lock(&data->stop);
                data->flag = 1;
                pthread_mutex_unlock(&data->stop);
                
                printf_mutex_dead(&data->philos[i], "%ld ms: philo %d died\n", new);

                return 0;
            }
            pthread_mutex_unlock(&data->philos[i].last_meal);
            
            
            pthread_mutex_lock(&data->philos[i].eat_mutex);
            pthread_mutex_lock(&data->philos[i].count_mutex);
            if (data->must_eat != -1 && data->philos[i].eat_count < data->must_eat)
                all_ate = 0;
            pthread_mutex_unlock(&data->philos[i].eat_mutex);
            pthread_mutex_unlock(&data->philos[i].count_mutex);
            
            i++;
        }
        if (data->must_eat != -1 && all_ate)
        {
            //pthread_mutex_lock(&data-philos->flag_mutex);
            pthread_mutex_lock(&data->stop); 
            data->flag = 1;
            pthread_mutex_unlock(&data->stop); 
            //pthread_mutex_lock(&data-philos->flag_mutex); 
            return 0;
        }

        usleep(200);
    }
    return 1;
}

int    should_stop(t_philo *philos)
{
    pthread_mutex_lock(philos->flag_mutex);

        if (*philos->stop)
        {
            pthread_mutex_unlock(philos->flag_mutex);
            return 1;
        }
        pthread_mutex_unlock(philos->flag_mutex);
        return 0;
}

void    is_eating(t_philo   *philos)
{
        pthread_mutex_lock(&philos->last_meal);
        philos->last_meal_time = get_time_in_ms();
        pthread_mutex_unlock(&philos->last_meal);

        printf_mutex(philos, "%ld ms: philo %d is eating\n", philos->last_meal_time);

        pthread_mutex_lock(&philos->count_mutex);
        philos->eat_count++;
        pthread_mutex_unlock(&philos->count_mutex);
        usleep(philos->time_to_eat * 1000);
}

void *routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;

    while (!*philos->stop)
    {
        if(should_stop(philos))
            break;
        if (!check_eating(philos))
            return NULL;
        is_eating(philos);
        pthread_mutex_unlock(philos->left_fork);
        pthread_mutex_unlock(philos->right_fork);
         if(should_stop(philos))
            break;
        printf_mutex(philos, "%ld ms: philo %d is sleeping\n", get_time_in_ms());
        usleep(philos->time_to_sleep * 1000);

        if(should_stop(philos))
            break;
        printf_mutex(philos, "%ld ms: philo %d is thinking\n", get_time_in_ms());
    }
    return NULL;
}


