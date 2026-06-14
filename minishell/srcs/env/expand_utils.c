/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:55 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:56 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, int *len)
{
	int	i;

	i = 0;
	if (str[i] == '?')
	{
		*len = 1;
		return (ft_strdup("?"));
	}
	while (str[i] && (str[i] == '_' || (str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')))
		i++;
	*len = i;
	return (ft_substr(str, 0, i));
}

static char	*get_status_str(int status)
{
	char	*status_str;
	int		len;
	int		tmp;

	if (status == 0)
		return (ft_strdup("0"));
	len = 0;
	tmp = status;
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	status_str = malloc(len + 1);
	if (!status_str)
		return (NULL);
	status_str[len] = '\0';
	while (len--)
	{
		status_str[len] = (status % 10) + '0';
		status /= 10;
	}
	return (status_str);
}

static char	*get_var_value(char *var_name, t_shell *shell)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		return (get_status_str(shell->last_exit_status));
	value = get_env_value(shell->env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*value;
	int		len;

	(*i)++;
	if (str[*i] == '\0' || str[*i] == ' ' || str[*i] == '\t'
		|| str[*i] == 3 || str[*i] == 4)
		return (ft_strdup("$"));
	var_name = get_var_name(str + *i, &len);
	if (!var_name || len == 0)
	{
		if (var_name)
			free(var_name);
		return (ft_strdup("$"));
	}
	*i += len;
	value = get_var_value(var_name, shell);
	free(var_name);
	return (value);
}

char	*join_parts(char *s1, char *s2)
{
	char	*ret;

	if (!s1 || !s2)
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (NULL);
	}
	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}
