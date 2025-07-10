/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:30:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/10 20:06:53 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

struct	s_data; //this line is to define the structure before actually saying what's inside it

typedef struct s_data
{
	int     philo_num;
        long    death_time;
        long    eat_time;
        long    sleep_time;
        long	must_eat_time;
		long	start_time;
} t_data;

typedef struct s_philo
{
	t_data  *data;
        int     id;
        pthread_t       thread;
        long    time_to_eat;
        long    time_to_sleep;
        long    time_to_death;
        long    time_to_start;
		long	must_eat;
		size_t	last_meal_time;
        pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
        pthread_mutex_t	*forks;
		pthread_mutex_t	*print_mutex;
} t_philo;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int s);
int valid_arg(char **argv);
void init_arg(char **argv,t_philo *philo);
void    init_philos(t_philo *philo);
int init_fork(t_philo *philo);
void *routine(void *arg);
void    init_threads(t_philo *philo);
long get_time_in_ms();
void    printf_mutex(t_philo *philo,char *str1,size_t num);
#endif

/*
typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	int				proper_meals;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	data_mutex;
	int				meals_eaten;
	int				num_times_eat;
	int				is_dead;
	int				stop_flag;
	pthread_mutex_t	*forks;
}					t_data;
typedef struct s_philo
{
	size_t			start_time;
	size_t			last_meal;
	size_t			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_t		thread;
	int				id;
	int				num_times_eat;
	int				meals_eaten;
	int				flag_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				num_philos;
	pthread_mutex_t	forks[PHILO_MAX];
	t_data			*data;
}
*/
