/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:14:29 by kato              #+#    #+#             */
/*   Updated: 2025/12/05 14:53:42 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long long			last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}						t_philo;

typedef struct s_data
{
	int					num_philos;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	int					must_eat_count;
	int					simulation_active;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		state_mutex;
	t_philo				*philos;
}						t_data;

int						main(int argc, char **argv);
void					cleanup(t_data *data);

void					init_meal_times(t_data *data);
int						create_threads(t_data *data, pthread_t *monitor);
void					join_threads(t_data *data, pthread_t monitor);
int						start_simulation(t_data *data);

int						init_data(t_data *data, int argc, char **argv);
int						init_mutexes(t_data *data);
int						init_philos(t_data *data);

int						ft_atoi(const char *str);
int						ft_isdigit(int c);
long long				get_time(void);
int						ft_usleep(long long time);

void					print_status(t_philo *philo, char *status);
int						is_simulation_active(t_data *data);
void					set_simulation_inactive(t_data *data);

void					*philosopher_routine(void *arg);

void					*monitor_routine(void *arg);

#endif
