/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 19:57:22 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/20 17:51:07 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_usleep(size_t time, t_philo *philo)
{
	size_t	start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < time)
	{
		if (should_stop(philo, 3))
			break ;
		usleep(50);
	}
}

void	*handle_one_philo(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	printf_mutex(philos, "%ld %d has taken a fork\n", get_time_in_ms());
	while (!should_stop(philos, 3))
		usleep(100);
	pthread_mutex_unlock(philos->left_fork);
	return (NULL);
}

void	printf_mutex(t_philo *philo, char *str, size_t timestamp)
{
	pthread_mutex_lock(philo->flag_mutex);
	if (!*philo->stop)
	{
		pthread_mutex_lock(philo->print_mutex);
		printf(str, timestamp - philo->start_time, philo->id);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_unlock(philo->flag_mutex);
	}
	else
	{
		pthread_mutex_unlock(philo->flag_mutex);
	}
}

void	printf_mutex_dead(t_philo *philo, char *str, size_t timestamp)
{
	pthread_mutex_lock(philo->print_mutex);
	printf(str, timestamp - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
