/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:10:44 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/12 22:00:58 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(char **av, t_shell *shell)
{
	if (!av || !av[0])
		return (1);
	if (ft_strcmp(av[0], "echo") == 0)
		return (builtin_echo(av));
	if (ft_strcmp(av[0], "cd") == 0)
		return (builtin_cd(av, shell));
	if (ft_strcmp(av[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(av[0], "export") == 0)
		return (builtin_export(av, shell));
	if (ft_strcmp(av[0], "unset") == 0)
		return (builtin_unset(av, shell));
	if (ft_strcmp(av[0], "env") == 0)
		return (builtin_env(av, shell));
	if (ft_strcmp(av[0], "exit") == 0)
		return (builtin_exit(av, shell));
	return (1);
}
