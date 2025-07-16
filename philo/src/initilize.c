/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:46 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/16 19:17:02 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void init_arg(char **argv,t_data * data)
{
    data->philo_num = 0;
    data->death_time = 0;
    data->eat_time = 0;
    data->sleep_time = 0;
    data->must_eat = 0;
    data->start_time = 0;
    data->flag = 0;
    data->philo_num = ft_atoi(argv[1]);
    data->death_time = ft_atoi(argv[2]);
    data->eat_time = ft_atoi(argv[3]);
    data->sleep_time = ft_atoi(argv[4]);
    if (argv[5])
        data->must_eat = ft_atoi(argv[5]);
    else
        data->must_eat = -1;  
    pthread_mutex_init(&data->print_mutex, NULL); 
    pthread_mutex_init(&data->stop, NULL); 
    pthread_mutex_init(&data->all_ate_mutex, NULL);
}
void    init_philos(t_data *data)
{
    int i = 0;
    t_philo *philos = data->philos;
    while (data->philo_num > i)
    {
        philos[i].stop = &data->flag;
        philos[i].id = i + 1;
        philos[i].time_to_death = data->death_time;
        philos[i].time_to_eat = data->eat_time;
        philos[i].time_to_sleep = data->sleep_time;
        if (data->must_eat != -1)
            philos[i].must_eat = data->must_eat;
        philos[i].eat_count = 0;
        philos[i].start_time = data->start_time;
        philos[i].left_fork = &data->forks[i];
        philos[i].right_fork = &data->forks[(i + 1) % data->philo_num];
        philos[i].print_mutex = &data->print_mutex;
        philos[i].flag_mutex = &data->stop;
        pthread_mutex_init(&philos[i].last_meal, NULL);
        pthread_mutex_init(&philos[i].eat_mutex, NULL);
        //pthread_mutex_init(&philos[i].flag_mutex, NULL);
        pthread_mutex_init(&philos[i].count_mutex, NULL);
        
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
int init_fork(t_data *data)
{
    int i = 0;
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
    if (!data->forks)
    {
        return 0;
    }
    while(i < data->philo_num)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    return 1;
}

void     printf_mutex(t_philo *philo,char *str,size_t timestamp)
{
    pthread_mutex_lock(philo->flag_mutex);
    if (!*philo->stop)
    {
        pthread_mutex_lock(philo->print_mutex);
        printf(str, timestamp - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->print_mutex);
        pthread_mutex_unlock(philo->flag_mutex);
    }
    //pthread_mutex_unlock(philo->flag_mutex);
}
void     printf_mutex_dead(t_philo *philo,char *str,size_t timestamp)
{
        pthread_mutex_lock(philo->print_mutex);
        printf(str, timestamp - philo->start_time, philo->id);
        pthread_mutex_unlock(philo->print_mutex);
}

int init_threads(t_data *data)
{
    int i = 0;
    size_t time = get_time_in_ms();
    data->start_time = time;

    while (i < data->philo_num)
    {
        data->philos[i].last_meal_time =  data->start_time;
        data->philos[i].start_time = data->start_time;
        i++;
    }

    i = 0;
    while (i < data->philo_num)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &routine, &data->philos[i]) != 0)
            return 0;
        i++;
    }
    monitor_death (data);
       
    i = 0;
    while (i < data->philo_num)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }

    return 1;
}

