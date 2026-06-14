/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:35 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/15 12:46:50 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **av, t_shell *shell)
{
	long long	num;

	if (!av[1])
	{
		write(1, "exit\n", 5);
		exit(shell->last_exit_status);
	}
	if (ft_atoll(av[1], &num))
	{
		write(1, "exit\n", 5);
		print_error("exit", av[1], "numeric argument required");
		exit(2);
	}
	if (av[2])
	{
		write(1, "exit\n", 5);
		print_error("exit", NULL, "too many arguments");
		return (1);
	}
	write(1, "exit\n", 5);
	exit((unsigned char)num);
}
