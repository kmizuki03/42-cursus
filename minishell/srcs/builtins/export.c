/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:38 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/18 02:49:42 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	**create_env_array(t_env *env, int count)
{
	t_env	**arr;
	int		i;

	arr = malloc(sizeof(t_env *) * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (env)
	{
		arr[i++] = env;
		env = env->next;
	}
	return (arr);
}

static void	print_export(t_env *env)
{
	t_env	**arr;
	int		count;
	int		i;

	count = count_env(env);
	if (count == 0)
		return ;
	arr = create_env_array(env, count);
	if (!arr)
		return ;
	sort_env_array(arr, count);
	i = -1;
	while (++i < count)
	{
		if (arr[i]->is_set)
			print_export_line(arr[i]->key, arr[i]->value);
		else
		{
			write(1, "declare -x ", 11);
			write(1, arr[i]->key, ft_strlen(arr[i]->key));
			write(1, "\n", 1);
		}
	}
	free(arr);
}

static int	append_env_var(char *arg, char *eq, t_shell *shell)
{
	char	*key;
	char	*old_val;
	char	*joined_val;
	int		res;

	key = ft_substr(arg, 0, eq - arg - 1);
	if (!key)
		return (1);
	old_val = get_env_value(shell->env, key);
	if (!old_val)
		old_val = "";
	joined_val = ft_strjoin(old_val, eq + 1);
	if (!joined_val)
	{
		free(key);
		return (1);
	}
	res = set_env_value(&shell->env, key, joined_val);
	free(key);
	free(joined_val);
	return (res == -1);
}

static int	export_var(char *arg, t_shell *shell)
{
	char	*eq;

	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	eq = ft_strchr(arg, '=');
	if (eq)
	{
		if (eq > arg && *(eq - 1) == '+')
			return (append_env_var(arg, eq, shell));
		*eq = '\0';
		set_env_value(&shell->env, arg, eq + 1);
		*eq = '=';
	}
	else
		declare_env(&shell->env, arg);
	return (0);
}

int	builtin_export(char **av, t_shell *shell)
{
	int		i;
	int		ret;

	if (!av[1])
	{
		print_export(shell->env);
		return (0);
	}
	ret = 0;
	i = 1;
	while (av[i])
	{
		if (export_var(av[i], shell) == 1)
			ret = 1;
		i++;
	}
	return (ret);
}
