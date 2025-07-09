/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:05 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/09 16:40:02 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc ,char **argv)
{
    t_philo *philo;
    if (argc < 5 || argc > 6)
        return 1;
    if (!valid_arg(argv))
        return 1;
    philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
    if (!philo)
        return 1;
    philo->data = malloc(sizeof(t_data));
    if (!philo->data)
        return 1;
    init_arg(argv,philo);
    init_philos(philo);
    printf("no_philo is:%d\n ",philo->data->philo_num);
    printf("time to dye:%ld\n ",philo->data->death_time);
    printf("time to eat:%ld\n ",philo->data->eat_time);
    printf("time to sleep:%ld\n ",philo->data->sleep_time);
    printf("must eat time:%ld\n ",philo->data->must_eat_time);
}