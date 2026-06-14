/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:11:56 by kato              #+#    #+#             */
/*   Updated: 2025/12/03 11:57:01 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->must_eat_count == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].meals_eaten < data->must_eat_count)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (all_ate)
	{
		set_simulation_inactive(data);
		return (1);
	}
	return (0);
}

static int	is_philo_dead(t_data *data, t_philo *philo)
{
	long long	current_time;

	pthread_mutex_lock(&data->meal_mutex);
	current_time = get_time();
	if ((current_time - philo->last_meal_time) >= data->time_to_die)
	{
		pthread_mutex_unlock(&data->meal_mutex);
		pthread_mutex_lock(&data->state_mutex);
		if (data->simulation_active)
		{
			data->simulation_active = 0;
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", current_time - data->start_time,
				philo->id);
			pthread_mutex_unlock(&data->print_mutex);
		}
		pthread_mutex_unlock(&data->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (0);
}

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (is_philo_dead(data, &data->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (is_simulation_active(data))
	{
		if (check_death(data))
			break ;
		if (check_all_ate(data))
			break ;
		usleep(200);
	}
	return (NULL);
}
