/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_death.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:03:13 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/17 20:43:00 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	size_t	now;
	int		i;

	now = get_time_in_ms();
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].last_meal);
		if (data->death_time < (now - data->philos[i].last_meal_time))
		{
			pthread_mutex_unlock(&data->philos[i].last_meal);
			pthread_mutex_lock(&data->stop);
			data->flag = 1;
			pthread_mutex_unlock(&data->stop);
			printf_mutex_dead(&data->philos[i], "%ld ms: philo %d died\n", now);
			return (1);
		}
		pthread_mutex_unlock(&data->philos[i].last_meal);
		i++;
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	i = 0;
	all_ate = 1;
	if (data->must_eat == -1)
		return (0);
	while (i < data->philo_num)
	{
		pthread_mutex_lock(&data->philos[i].eat_mutex);
		pthread_mutex_lock(&data->philos[i].count_mutex);
		if (data->philos[i].eat_count < data->must_eat)
			all_ate = 0;
		pthread_mutex_unlock(&data->philos[i].eat_mutex);
		pthread_mutex_unlock(&data->philos[i].count_mutex);
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->stop);
		data->flag = 1;
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	return (0);
}

int	monitor_death(t_data *data)
{
	if (data->philo_num == 1)
	{
		smart_usleep(data->death_time);
		pthread_mutex_lock(&data->stop);
		data->flag = 1;
		pthread_mutex_unlock(&data->stop);
		printf_mutex_dead(&data->philos[0], "%ld ms: philo %d died\n",
			get_time_in_ms());
		return (0);
	}
	while (1)
	{
		if (check_death(data))
			return (0);
		if (check_all_ate(data))
			return (0);
		usleep(200);
	}
	return (1);
}
