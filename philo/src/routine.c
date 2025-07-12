/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/12 20:29:15 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}
int monitor_death(t_philo *philo)
{
    long now;
    int i;

    while (!philo->data->flag)
    {
        i = 0;
        while (i < philo->data->philo_num)
        {
            now = get_time_in_ms();
            if ((now - philo[i].last_meal_time) >= philo->time_to_death)
            {
                philo->data->flag = 1;
                printf_mutex(&philo[i], "%ld ms: philo %d is dying\n", now);
                return 0;
            }
            i++;
        }
    }
    return 1;
}



void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->data->flag)
    {
        if (philo->data->flag)
            break;
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->right_fork);
            if (philo->data->flag) {
                pthread_mutex_unlock(philo->right_fork);
                break;
            }
            printf_mutex(philo, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());

            pthread_mutex_lock(philo->left_fork);
            if (philo->data->flag) {
                pthread_mutex_unlock(philo->left_fork);
                pthread_mutex_unlock(philo->right_fork);
                break;
            }
            printf_mutex(philo, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
        } 
        else 
        {
            pthread_mutex_lock(philo->left_fork);
            if (philo->data->flag) {
                pthread_mutex_unlock(philo->left_fork);
                break;
            }
            printf_mutex(philo, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());

            pthread_mutex_lock(philo->right_fork);
            if (philo->data->flag) {
                pthread_mutex_unlock(philo->right_fork);
                pthread_mutex_unlock(philo->left_fork);
                break;
            }
            printf_mutex(philo, "%ld ms: philo %d has taken a fork\n", get_time_in_ms());
        }

        philo->last_meal_time = get_time_in_ms();
        printf_mutex(philo, "%ld ms: philo %d is eating\n", philo->last_meal_time);

        usleep(philo->data->eat_time * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        if (philo->data->flag)
            break;
        printf_mutex(philo, "%ld ms: philo %d is sleeping\n", get_time_in_ms());
        usleep(philo->data->sleep_time * 1000);

        if (philo->data->flag)
            break;
        printf_mutex(philo, "%ld ms: philo %d is thinking\n", get_time_in_ms());
    }

    return NULL;
}

