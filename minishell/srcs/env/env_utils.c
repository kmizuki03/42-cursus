/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:49 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*make_env_str(t_env *env)
{
	char	*eq_join;
	char	*ret;

	eq_join = ft_strjoin(env->key, "=");
	if (!eq_join)
		return (NULL);
	ret = ft_strjoin(eq_join, env->value);
	free(eq_join);
	return (ret);
}

static int	count_set_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->is_set)
			count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**ret;
	int		count;
	int		i;

	count = count_set_env(env);
	ret = malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->is_set)
		{
			ret[i] = make_env_str(env);
			if (!ret[i])
				return (free_array(ret), NULL);
			i++;
		}
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
