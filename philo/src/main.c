/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:22:05 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/15 20:00:08 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int main(int argc ,char **argv)
// {
//     t_data *data;
//     if (argc < 5 || argc > 6)
//         return 1;
//     if (!valid_arg(argv))
//         return 1;
//     data = malloc(sizeof(t_data));
//     if (!data)
//         return 1;
//     data->philos = malloc(sizeof(t_philo)* ft_atoi(argv[1]));
//     if (!data->philos)
//         return 1;
//     init_arg(argv,data);
//     if(!init_fork(data))
//         return 1;
//     init_philos(data);
//     if (init_threads(data))
//         return 0;
//    pthread_mutex_destroy(&data->print_mutex);
// free(data->print_mutex);
// free(data->forks);
// free(data->philos);
// free(data);
// }

int main(int argc ,char **argv)
{
    t_data *data;
    int i;

    if (argc < 5 || argc > 6)
        return 1;
    if (!valid_arg(argv))
        return 1;
    data = malloc(sizeof(t_data));
    if (!data)
        return 1;
    data->philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
    if (!data->philos) {
        free(data);
        return 1;
    }
    init_arg(argv, data);
    if (!init_fork(data)) {
        free(data->philos);
        free(data);
        return 1;
    }
    init_philos(data);
    if (!init_threads(data)) {
        i = 0;
        while (i < data->philo_num)
            pthread_mutex_destroy(&data->forks[i++]);
        pthread_mutex_destroy(&data->print_mutex);
        free(data->forks);
        free(data->philos);
        free(data);
        return 1;
    }
    i = 0;
    while (i < data->philo_num)
        pthread_mutex_destroy(&data->forks[i++]);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->stop);
    //pthread_mutex_destroy(&data->philos[i].last_meal);
    //pthread_mutex_destroy(&data->philos[i].eat_mutex);
    free(data->forks);
    free(data->philos);
    free(data);
    return 0;
}