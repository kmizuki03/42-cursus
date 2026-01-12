/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tilde.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 22:26:50 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/11 22:26:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_quoted(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == 1 || value[i] == 3)
			return (1);
		i++;
	}
	return (0);
}

char	*expand_tilde_token(char *value, t_shell *shell)
{
	char	*home;
	char	*result;
	char	*expanded;

	expanded = expand_variables(value, shell);
	if (!expanded)
		return (NULL);
	if (expanded[0] != '~' || is_token_quoted(value))
		return (expanded);
	home = get_env_value(shell->env, "HOME");
	if (!home)
		return (expanded);
	if (expanded[1] == '\0')
	{
		free(expanded);
		return (ft_strdup(home));
	}
	if (expanded[1] == '/')
	{
		result = ft_strjoin(home, expanded + 1);
		free(expanded);
		return (result);
	}
	return (expanded);
}
