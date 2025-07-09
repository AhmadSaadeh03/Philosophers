/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:46 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/09 17:20:50 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void init_arg(char **argv,t_philo *philo)
{
    philo->data->philo_num = 0;
    philo->data->death_time = 0;
    philo->data->eat_time = 0;
    philo->data->sleep_time = 0;
    philo->data->must_eat_time = 0;
    philo->data->philo_num = ft_atoi(argv[1]);
    philo->data->death_time = ft_atoi(argv[2]);
    philo->data->eat_time = ft_atoi(argv[3]);
    philo->data->sleep_time = ft_atoi(argv[4]);
    if (argv[5])
        philo->data->must_eat_time = ft_atoi(argv[5]);
    else
        philo->data->must_eat_time = -1;   
}
void    init_philos(t_philo *philo)
{
    int i = 0;
    while (philo->data->philo_num > i)
    {
        philo[i].id = i+1;
        philo[i].time_to_death = philo->data->death_time;
        philo[i].time_to_eat = philo->data->eat_time;
        philo[i].time_to_sleep = philo->data->sleep_time;
        if (philo->data->must_eat_time != -1)
            philo[i].must_eat = philo->data->must_eat_time;
        
        i++;

    }
     i = 0;
    while(i < philo->data->philo_num )
    {
        printf("%d\n",philo[i].id);
        printf("%ld\n",philo[i].time_to_death);
        printf("%ld\n",philo[i].time_to_eat);
        printf("%ld\n",philo[i].time_to_sleep);
        printf("%ld\n",philo[i].must_eat);

       i++;
    }
    
}
void init_fork(t_philo *philo)
{
    int i = 0;
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->data->philo_num);
    while(i < philo->data->philo_num)
    {
        pthread_mutex_init(&philo->forks[i], NULL);
        i++;
    }
}