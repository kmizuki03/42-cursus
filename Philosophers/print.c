/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 00:11:07 by kato              #+#    #+#             */
/*   Updated: 2025/12/03 00:11:08 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *status)
{
	long long	timestamp;

	pthread_mutex_lock(&philo->data->state_mutex);
	if (philo->data->simulation_active)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		timestamp = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, status);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->state_mutex);
}

int	is_simulation_active(t_data *data)
{
	int	active;

	pthread_mutex_lock(&data->state_mutex);
	active = data->simulation_active;
	pthread_mutex_unlock(&data->state_mutex);
	return (active);
}

void	set_simulation_inactive(t_data *data)
{
	pthread_mutex_lock(&data->state_mutex);
	data->simulation_active = 0;
	pthread_mutex_unlock(&data->state_mutex);
}
