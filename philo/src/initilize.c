/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:44:46 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/20 18:09:27 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arg(char **argv, t_data *data)
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
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->stop, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philo_mutexes(t_philo *philo)
{
	if (pthread_mutex_init(&philo->last_meal, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&philo->count_mutex, NULL) != 0)
		return (0);
	return (1);
}

static int	init_philo_fields(t_data *data, t_philo *philo, int i)
{
	philo->stop = &data->flag;
	philo->id = i + 1;
	philo->time_to_death = data->death_time;
	philo->time_to_eat = data->eat_time;
	philo->time_to_sleep = data->sleep_time;
	philo->philo_num = data->philo_num;
	if (data->must_eat != -1)
		philo->must_eat = data->must_eat;
	philo->eat_count = 0;
	philo->start_time = data->start_time;
	philo->left_fork = &data->forks[i];
	philo->right_fork = &data->forks[(i + 1) % data->philo_num];
	philo->print_mutex = &data->print_mutex;
	philo->flag_mutex = &data->stop;
	return (1);
}

int	init_philos(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = 0;
	while (i < data->philo_num)
	{
		if (!init_philo_fields(data, &philos[i], i))
			return (0);
		if (!init_philo_mutexes(&philos[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		return (0);
	}
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (1);
}
