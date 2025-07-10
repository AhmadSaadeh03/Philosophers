/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/10 20:58:49 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_time_in_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

// void *routine(void *arg)
// {
//     t_philo *philo = (t_philo *)arg;
//         long now = get_time_in_ms();
    
//         // printf("philo %d start thinking ...\n",philo->id);
//         // pthread_mutex_lock(philo->left_fork);
//         // printf("philo %d taking left fork ...\n",philo->id);
//         // pthread_mutex_lock(philo->right_fork);
//         // printf("philo %d taking right fork ...\n",philo->id);
//         // philo->last_meal_time = get_time_in_ms();
//         // printf("philo %d is eating ...\n",philo->id);
//         // usleep(philo->data->eat_time * 1000);
//         // pthread_mutex_unlock(philo->right_fork);
//         // pthread_mutex_unlock(philo->left_fork);
//         // printf("philo %ds is sleeping ...\n",philo->id);
//         // usleep(philo->data->sleep_time * 1000);
//          printf("%ld ms: philo %d is thinking\n", now - philo->data->start_time, philo->id);

//         pthread_mutex_lock(philo->left_fork);
//         printf("%ld ms: philo %d took left fork\n", get_time_in_ms() - philo->data->start_time, philo->id);

//         pthread_mutex_lock(philo->right_fork);
//         printf("%ld ms: philo %d took right fork\n", get_time_in_ms() - philo->data->start_time, philo->id);

//         philo->last_meal_time = get_time_in_ms();
//         printf("%ld ms: philo %d is eating\n", philo->last_meal_time - philo->data->start_time, philo->id);
//         usleep(philo->data->eat_time * 1000);

//         pthread_mutex_unlock(philo->right_fork);
//         pthread_mutex_unlock(philo->left_fork);

//         printf("%ld ms: philo %d is sleeping\n", get_time_in_ms() - philo->data->start_time, philo->id);
//         usleep(philo->data->sleep_time * 1000);
//     return NULL;
// }

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1) 
    {
        size_t timestamp = get_time_in_ms();
        printf_mutex(philo,"%ld ms: philo %d is thinking\n",timestamp);   
        if (philo->id % 2 == 0) {
            pthread_mutex_lock(philo->right_fork);
            printf_mutex(philo,"%ld ms: philo %d  has taken a fork\n", timestamp);
            pthread_mutex_lock(philo->left_fork);
            printf_mutex(philo,"%ld ms: philo %d  has taken a fork\n", timestamp);
        } 
        else 
        {
            pthread_mutex_lock(philo->left_fork);
            printf_mutex(philo,"%ld ms: philo %d  has taken a fork\n", timestamp);
            pthread_mutex_lock(philo->right_fork);
           printf_mutex(philo,"%ld ms: philo %d  has taken a fork\n", timestamp);
        }
        
        philo->last_meal_time = timestamp;
        printf_mutex(philo,"%ld ms: philo %d is eating\n", philo->last_meal_time);
        usleep(philo->data->eat_time * 1000);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        printf_mutex(philo,"%ld ms: philo %d is sleeping\n", timestamp);
        usleep(philo->data->sleep_time * 1000);
    }
    return NULL;
}

