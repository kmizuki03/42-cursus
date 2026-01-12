/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:32 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 20:03:46 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || !arg[1])
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_echo(char **av)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (av[i] && is_n_flag(av[i]))
	{
		newline = 0;
		i++;
	}
	while (av[i])
	{
		write(1, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
