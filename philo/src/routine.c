/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/13 19:35:31 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int monitor_death(t_data *data)
{
    long now;
    int i;
    int all_ate;
    
    while (!data->flag)
    {
        i = 0;
        all_ate = 1;
        while (i < data->philo_num)
        {
            now = get_time_in_ms();
            // mutex last meal
            pthread_mutex_lock(&data->philos[i].last_meal);
            if ((now - data->philos[i].last_meal_time) > data->death_time)
            {
                pthread_mutex_unlock(&data->philos[i].last_meal);
                // stop mutex
                pthread_mutex_lock(&data->stop);
                data->flag = 1;
                pthread_mutex_unlock(&data->stop);
                printf_mutex(&data->philos[i], "%ld ms: philo %d died\n", now);
                return 0;
            }
            pthread_mutex_unlock(&data->philos[i].last_meal);
            pthread_mutex_lock(&data->philos[i].eat_mutex);
            if (data->must_eat != -1 && data->philos[i].eat_count < data->must_eat)
                all_ate = 0;
            pthread_mutex_unlock(&data->philos[i].eat_mutex);
            i++;
        }
        if (data->must_eat != -1 && all_ate)
        {
            // stop mutex
             pthread_mutex_lock(&data->stop);
            data->flag = 1;
             pthread_mutex_unlock(&data->stop);
            return 0;
        }
        // mutex last meal
        usleep(200);
    }
    return 1;
}

void *routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;

    while (!*philos->flag)
    {
        if (*philos->flag)
            break;
        if (philos->id % 2 == 0) {
            pthread_mutex_lock(philos->right_fork);
            if (*philos->flag) {
                pthread_mutex_unlock(philos->right_fork);
                break;
            }
            printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());

            pthread_mutex_lock(philos->left_fork);
            if (*philos->flag) {
                pthread_mutex_unlock(philos->left_fork);
                pthread_mutex_unlock(philos->right_fork);
                break;
            }
            printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
        } 
        else 
        {
            pthread_mutex_lock(philos->left_fork);
            if (*philos->flag) {
                pthread_mutex_unlock(philos->left_fork);
                break;
            }
            printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());

            pthread_mutex_lock(philos->right_fork);
            if (*philos->flag) {
                pthread_mutex_unlock(philos->right_fork);
                pthread_mutex_unlock(philos->left_fork);
                break;
            }
            printf_mutex(philos, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
        }

        philos->last_meal_time = get_time_in_ms();
        printf_mutex(philos, "%ld ms: philo %d is eating\n", philos->last_meal_time);
        philos->eat_count++;
        // while (!should_stop && time < time to eat)
        //  usleep 100
        usleep(philos->time_to_eat * 1000);

        pthread_mutex_unlock(philos->left_fork);
        pthread_mutex_unlock(philos->right_fork);

        if (*philos->flag)
            break;
        printf_mutex(philos, "%ld ms: philo %d is sleeping\n", get_time_in_ms());
        ///
        usleep(philos->time_to_sleep * 1000);

        if (*philos->flag)
            break;
        printf_mutex(philos, "%ld ms: philo %d is thinking\n", get_time_in_ms());
    }
    return NULL;
}