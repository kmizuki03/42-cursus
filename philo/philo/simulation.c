/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:49:59 by kato              #+#    #+#             */
/*   Updated: 2025/12/03 13:49:59 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_meal_times(t_data *data)
{
	int	i;

	data->start_time = get_time();
	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].last_meal_time = data->start_time;
		i++;
	}
}

static void	join_failed_threads(t_data *data, int count)
{
	set_simulation_inactive(data);
	while (count > 0)
	{
		count--;
		pthread_join(data->philos[count].thread, NULL);
	}
}

int	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philosopher_routine,
				&data->philos[i]) != 0)
		{
			join_failed_threads(data, i);
			return (1);
		}
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		join_failed_threads(data, data->num_philos);
		return (1);
	}
	return (0);
}

void	join_threads(t_data *data, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	pthread_t	monitor;

	init_meal_times(data);
	if (create_threads(data, &monitor) != 0)
		return (1);
	join_threads(data, monitor);
	return (0);
}
