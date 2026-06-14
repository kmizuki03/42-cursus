/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:34 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:35 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **av, t_shell *shell)
{
	t_env	*env;

	(void)av;
	env = shell->env;
	while (env)
	{
		if (env->is_set)
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}
