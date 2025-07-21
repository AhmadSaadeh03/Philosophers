/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:05 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/20 18:15:50 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->philos[i].last_meal);
		pthread_mutex_destroy(&data->philos[i].count_mutex);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop);
	free(data->forks);
	free(data->philos);
	free(data);
}

static int	check_arg(t_data *data)
{
	if (data->philo_num < 1 || data->philo_num > 200)
		return (0);
	if (data->death_time < 60 || data->eat_time < 60 || data->sleep_time < 60)
		return (0);
	return (1);
}

void	free_dataphilo(t_data *data)
{
	free(data->philos);
	free(data);
}

static int	is_succsess(char **argv, t_data *data)
{
	if (!init_arg(argv, data))
	{
		free_dataphilo(data);
		return (0);
	}
	if (check_arg(data) == 0)
	{
		free_dataphilo(data);
		return (0);
	}
	if (!init_fork(data))
	{
		free_dataphilo(data);
		return (0);
	}
	if (!init_philos(data))
	{
		free(data->forks);
		free(data->philos);
		free(data);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6 || !valid_arg(argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	data->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!data->philos)
	{
		free(data);
		return (1);
	}
	if (!is_succsess(argv, data))
		return (1);
	if (!init_threads(data))
	{
		free_all(data);
		return (1);
	}
	free_all(data);
	return (0);
}
