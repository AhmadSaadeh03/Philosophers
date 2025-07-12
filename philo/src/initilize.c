/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:46 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/12 20:29:48 by asaadeh          ###   ########.fr       */
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
    philo->data->start_time = 0;
    philo->data->flag = 0;
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
        philo[i].data = philo->data;//here
        philo[i].time_to_death = philo->data->death_time;
        philo[i].time_to_eat = philo->data->eat_time;
        philo[i].time_to_sleep = philo->data->sleep_time;
        if (philo->data->must_eat_time != -1)
            philo[i].must_eat = philo->data->must_eat_time;
        philo[i].forks = philo->forks;//here
        philo[i].left_fork = &philo->forks[i];
        philo[i].right_fork = &philo->forks[(i + 1) % philo->data->philo_num];
        

        i++;
    }
    //  i = 0;
    // while(i < philo->data->philo_num )
    // {
    //     printf("%d\n",philo[i].id);
    //     printf("%ld\n",philo[i].time_to_death);
    //     printf("%ld\n",philo[i].time_to_eat);
    //     printf("%ld\n",philo[i].time_to_sleep);
    //     if (philo->data->must_eat_time != -1)
    //         printf("%ld\n",philo[i].must_eat);
        
    //    i++;
    // }
    
}
int init_fork(t_philo *philo)
{
    int i = 0;
    philo->forks = malloc(sizeof(pthread_mutex_t) * philo->data->philo_num);
    if (!philo->forks)
    {
        return 0;
    }
    while(i < philo->data->philo_num)
    {
        pthread_mutex_init(&philo->forks[i], NULL);
        i++;
    }
    return 1;
}
void     printf_mutex(t_philo *philo,char *str,long timestamp)
{
    philo->print_mutex = malloc(sizeof(pthread_mutex_t));
    
    pthread_mutex_init(philo->print_mutex,NULL);
    pthread_mutex_lock(philo->print_mutex);
    printf(str, timestamp - philo->data->start_time, philo->id);
    pthread_mutex_unlock(philo->print_mutex);
}
// int    init_threads(t_philo *philo)
// {
//     int i = 0;
//     philo->data->start_time = get_time_in_ms();
//     while (i < philo->data->philo_num)
//     {
//        if ((pthread_create(&philo[i].thread, NULL, &routine, &philo[i])) != 0)
//             return 0;
//         i++;
//     }
//     i = 0;
//     monitor_death(philo);
//     while (i < philo->data->philo_num)
//     {
//         pthread_join(philo[i].thread,NULL);
//         i++;
//     }
//     return 1;
    
// }
int init_threads(t_philo *philo)
{
    int i = 0;
    long start = get_time_in_ms();
    philo->data->start_time = start;

    while (i < philo->data->philo_num)
    {
        philo[i].last_meal_time = start;
        i++;
    }

    i = 0;
    while (i < philo->data->philo_num)
    {
        if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
            return 0;
        i++;
    }

    monitor_death(philo);

    i = 0;
    while (i < philo->data->philo_num)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }

    return 1;
}

