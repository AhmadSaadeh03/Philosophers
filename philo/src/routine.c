/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:21:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/19 20:50:03 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	even_philo(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	if (should_stop_cont(philos, 1))
		return (0);
	printf_mutex(philos, "%ld %d has taken a fork\n", get_time_in_ms());
	pthread_mutex_lock(philos->right_fork);
	if (should_stop(philos, 10))
		return (0);
	printf_mutex(philos, "%ld %d has taken a fork\n", get_time_in_ms());
	return (1);
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
		printf_mutex(philos, "%ld %d has taken a fork\n", get_time_in_ms());
		pthread_mutex_lock(philos->left_fork);
		if (should_stop(philos, 10))
			return (0);
		printf_mutex(philos, "%ld %d has taken a fork\n", get_time_in_ms());
	}
	else if (philos->id % 2 == 1)
	{
		if (!even_philo(philos))
			return (0);
	}
	return (1);
}

static int	is_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->last_meal);
	philos->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philos->last_meal);
	printf_mutex(philos, "%ld %d is eating\n", philos->last_meal_time);
	pthread_mutex_lock(&philos->count_mutex);
	philos->eat_count++;
	pthread_mutex_unlock(&philos->count_mutex);
	smart_usleep(philos->time_to_eat);
	return (1);
}

static void	is_sleeping(t_philo *philo)
{
	if (should_stop(philo, 3))
		return ;
	printf_mutex(philo, "%ld %d is sleeping\n", get_time_in_ms());
	smart_usleep(philo->time_to_sleep);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->philo_num == 1)
			return (handle_one_philo(philo));
		if (should_stop(philo, 3))
			break ;
		if (!check_eating(philo))
			break ;
		is_eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (should_stop(philo, 3))
			break ;
		is_sleeping(philo);
		if (should_stop(philo, 3))
			break ;
		usleep(20);
		printf_mutex(philo, "%ld %d is thinking\n", get_time_in_ms());
	}
	return (NULL);
}
