/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:30:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/07/19 20:47:09 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				*stop;
	int				id;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_to_death;
	size_t			time_to_start;
	long			must_eat;
	size_t			last_meal_time;
	long			eat_count;
	size_t			start_time;
	int				philo_num;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	last_meal;
	pthread_mutex_t	*flag_mutex;
	pthread_mutex_t	count_mutex;
}					t_philo;

typedef struct s_data
{
	int				flag;
	int				philo_num;
	size_t			death_time;
	size_t			eat_time;
	size_t			sleep_time;
	long			must_eat;
	size_t			start_time;
	size_t			current_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop;
	pthread_mutex_t	print_mutex;

}					t_data;

int					ft_atoi(const char *nptr);
int					ft_isdigit(int s);
int					valid_arg(char **argv);
void				init_arg(char **argv, t_data *data);
void				init_philos(t_data *data);
int					init_fork(t_data *data);
void				*routine(void *arg);
int					init_threads(t_data *data);
size_t				get_time_in_ms(void);
void				printf_mutex(t_philo *philo, char *str, size_t timestamp);
void				printf_mutex_dead(t_philo *philo, char *str,
						size_t timestamp);
int					monitor_death(t_data *data);
void				*handle_one_philo(t_philo *philos);
void				smart_usleep(size_t time);
int					should_stop(t_philo *philos, int mode);
int					should_stop_cont(t_philo *philos, int mode);

#endif