/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:47 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:48 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	if (!node->key || (value && !node->value))
	{
		free(node->key);
		free(node->value);
		free(node);
		return (NULL);
	}
	node->is_set = (value != NULL);
	node->next = NULL;
	return (node);
}

void	add_env_to_list(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (!*env)
		*env = new;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_env	*process_env_line(char *line, t_env *env)
{
	char	*eq;
	t_env	*new;

	eq = ft_strchr(line, '=');
	if (eq)
	{
		*eq = '\0';
		new = new_env_node(line, eq + 1);
		*eq = '=';
		if (!new)
			return (free_env(env), NULL);
		add_env_to_list(&env, new);
	}
	return (env);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		env = process_env_line(envp[i], env);
		if (!env && ft_strchr(envp[i], '='))
			return (NULL);
		i++;
	}
	return (env);
}
