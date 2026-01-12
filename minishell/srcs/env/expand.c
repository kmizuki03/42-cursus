/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:56 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:17:57 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_quoted_part(char *str, int *i, char *ret)
{
	char	*tmp;
	int		start;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != 2)
		(*i)++;
	tmp = ft_substr(str, start, *i - start);
	if (!tmp)
		return (free(ret), NULL);
	ret = join_parts(ret, tmp);
	if (str[*i] == 2)
		(*i)++;
	return (ret);
}

static char	*handle_text(char *str, int *i, char *ret)
{
	char	*tmp;
	int		start;

	start = *i;
	while (str[*i] && str[*i] != '$' && str[*i] != 1
		&& str[*i] != 3 && str[*i] != 4)
		(*i)++;
	if (*i > start)
	{
		tmp = ft_substr(str, start, *i - start);
		if (!tmp)
			return (free(ret), NULL);
		ret = join_parts(ret, tmp);
	}
	return (ret);
}

static char	*expand_loop(char *str, char *ret, t_shell *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && ret)
	{
		if (str[i] == 1)
			ret = handle_quoted_part(str, &i, ret);
		else
		{
			ret = handle_text(str, &i, ret);
			if (ret && str[i] == '$')
			{
				tmp = expand_var(str, &i, shell);
				if (tmp)
					ret = join_parts(ret, tmp);
				else
					return (free(ret), NULL);
			}
			else if (ret && (str[i] == 3 || str[i] == 4))
				i++;
		}
	}
	return (ret);
}

char	*remove_markers(char *str)
{
	char	*ret;
	int		i;
	int		j;

	ret = malloc(ft_strlen(str) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != 1 && str[i] != 2 && str[i] != 3 && str[i] != 4)
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*expand_variables(char *str, t_shell *shell)
{
	char	*ret;
	char	*final;

	if (!str)
		return (NULL);
	ret = ft_strdup("");
	if (!ret)
		return (NULL);
	ret = expand_loop(str, ret, shell);
	if (!ret)
		return (NULL);
	final = remove_markers(ret);
	free(ret);
	return (final);
}
