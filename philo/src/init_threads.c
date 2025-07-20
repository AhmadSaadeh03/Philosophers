/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 17:13:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/20 17:22:48 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	init_threads(t_data *data)
{
	int		i;
	size_t	time;

	i = 0;
	time = get_time_in_ms();
	data->start_time = time;
	while (i < data->philo_num)
	{
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].start_time = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			return (0);
		i++;
	}
	monitor_death(data);
	if (!ft_join(data))
		return (0);
	return (1);
}
