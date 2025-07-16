/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:30:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/16 19:17:13 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stddef.h>
struct	s_data; //this line is to define the structure before actually saying what's inside it

typedef struct s_philo
{
	int		*stop;
	int     id;
	size_t    time_to_eat;
	size_t    time_to_sleep;
	size_t    time_to_death;
	size_t    time_to_start;
	long	must_eat;
	size_t	last_meal_time;
	long	eat_count;
	size_t	start_time;
	pthread_t       thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal;
	pthread_mutex_t eat_mutex;
	pthread_mutex_t *flag_mutex;
	pthread_mutex_t	count_mutex;
} t_philo;


typedef struct s_data
{
	int 	flag;
	int     philo_num;
	size_t    death_time;
	size_t    eat_time;
	size_t    sleep_time;
	long	must_eat;
	size_t	start_time;
	size_t	current_time;
	t_philo *philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t all_ate_mutex;

} t_data;


int	ft_atoi(const char *nptr);
int	ft_isdigit(int s);
int valid_arg(char **argv);
void init_arg(char **argv,t_data *data);
void    init_philos(t_data *data);
int init_fork(t_data *data);
void *routine(void *arg);
int init_threads(t_data *data);
size_t get_time_in_ms();
void     printf_mutex(t_philo *philo,char *str,size_t timestamp);
void     printf_mutex_dead(t_philo *philo,char *str,size_t timestamp);
int monitor_death(t_data *data);
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
