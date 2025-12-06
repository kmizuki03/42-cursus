/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 13:50:15 by kato              #+#    #+#             */
/*   Updated: 2025/12/03 13:50:15 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid_num_str(char *str)
{
	int	j;

	j = 0;
	if (!str[0])
		return (0);
	while (str[j])
	{
		if (j == 0 && str[j] == '+')
		{
			if (!str[j + 1])
				return (0);
		}
		else if (!ft_isdigit(str[j]))
			return (0);
		j++;
	}
	return (1);
}

static int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die ", argv[0]);
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_valid_num_str(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	initialize_all(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
	{
		printf("Error: Invalid input values\n");
		return (1);
	}
	if (init_mutexes(data))
	{
		printf("Error: Mutex initialization failed\n");
		return (1);
	}
	if (init_philos(data))
	{
		printf("Error: Philosopher initialization failed\n");
		cleanup(data);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_args(argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (initialize_all(&data, argc, argv))
		return (1);
	if (start_simulation(&data))
	{
		printf("Error: Simulation failed\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->state_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}
