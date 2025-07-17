/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/17 20:33:24 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	should_stop_cont(t_philo *philos, int mode)
{
	if (mode == 0)
	{
		pthread_mutex_lock(philos->flag_mutex);
		if (*philos->stop)
		{
			pthread_mutex_unlock(philos->flag_mutex);
			pthread_mutex_unlock(philos->right_fork);
			return (1);
		}
		pthread_mutex_unlock(philos->flag_mutex);
	}
	if (mode == 1)
	{
		pthread_mutex_lock(philos->flag_mutex);
		if (*philos->stop)
		{
			pthread_mutex_unlock(philos->flag_mutex);
			pthread_mutex_unlock(philos->left_fork);
			return (1);
		}
		pthread_mutex_unlock(philos->flag_mutex);
	}
	return (0);
}

int	should_stop(t_philo *philos, int mode)
{
	if (mode == 3)
	{
		pthread_mutex_lock(philos->flag_mutex);
		if (*philos->stop)
		{
			pthread_mutex_unlock(philos->flag_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos->flag_mutex);
	}
	if (mode == 10)
	{
		pthread_mutex_lock(philos->flag_mutex);
		if (*philos->stop)
		{
			pthread_mutex_unlock(philos->right_fork);
			pthread_mutex_unlock(philos->left_fork);
			pthread_mutex_unlock(philos->flag_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos->flag_mutex);
	}
	return (0);
}

static int	check_eating(t_philo *philos)
{
	if (should_stop(philos, 3))
		return (0);
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		if (should_stop_cont(philos, 0))
			return (0);
		printf_mutex(philos, "%ld ms: philo %d has taken a fork\n",
			get_time_in_ms());
		pthread_mutex_lock(philos->left_fork);
		if (should_stop(philos, 10))
			return (0);
		printf_mutex(philos, "%ld ms: philo %d has taken a fork\n",
			get_time_in_ms());
	}
	else if (philos->id % 2 == 1)
	{
		pthread_mutex_lock(philos->left_fork);
		if (should_stop_cont(philos, 1))
			return (0);
		printf_mutex(philos, "%ld ms: philo %d has taken a fork\n",
			get_time_in_ms());
		pthread_mutex_lock(philos->right_fork);
		if (should_stop(philos, 10))
			return (0);
		printf_mutex(philos, "%ld ms: philo %d has taken a fork\n",
			get_time_in_ms());
	}
	return (1);
}

static void	is_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->last_meal);
	philos->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philos->last_meal);
	printf_mutex(philos, "%ld ms: philo %d is eating\n",
		philos->last_meal_time);
	pthread_mutex_lock(&philos->count_mutex);
	philos->eat_count++;
	pthread_mutex_unlock(&philos->count_mutex);
	smart_usleep(philos->time_to_eat);
}

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (philos->philo_num == 1)
			return (handle_one_philo(philos));
		if (should_stop(philos, 3))
			break ;
		if (!check_eating(philos))
			return (NULL);
		is_eating(philos);
		pthread_mutex_unlock(philos->left_fork);
		pthread_mutex_unlock(philos->right_fork);
		if (should_stop(philos, 3))
			break ;
		printf_mutex(philos, "%ld ms: philo %d is sleeping\n",
			get_time_in_ms());
		smart_usleep(philos->time_to_sleep);
		if (should_stop(philos, 3))
			break ;
		usleep(20);
		printf_mutex(philos, "%ld ms: philo %d is thinking\n",
			get_time_in_ms());
	}
	return (NULL);
}
