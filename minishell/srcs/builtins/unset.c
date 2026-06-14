/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:42 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:43 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_unset(char **av, t_shell *shell)
{
	int	i;

	if (!av[1])
		return (0);
	i = 1;
	while (av[i])
	{
		unset_env_value(&shell->env, av[i]);
		i++;
	}
	return (0);
}
