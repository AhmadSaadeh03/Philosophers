/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:17:03 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/19 20:43:49 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop_cont(t_philo *philos, int mode)
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
