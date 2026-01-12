/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/12 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	count_wildcard_matches(char **exp)
{
	int	i;

	if (!exp)
		return (1);
	i = 0;
	while (exp[i])
		i++;
	free_array(exp);
	return (i);
}

int	is_word_with_wildcard(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i] && token->value[i] != 1
		&& token->value[i] != 3)
		i++;
	if (token->value[i] || !has_wildcard(token->value))
		return (0);
	return (1);
}

int	is_quoted_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1 || str[i] == 3)
			return (1);
		i++;
	}
	return (0);
}

int	add_split_words(char **av, char **words, int *idx)
{
	int	i;

	i = 0;
	while (words && words[i])
	{
		av[(*idx)++] = words[i];
		i++;
	}
	if (words)
		free(words);
	return (0);
}

int	handle_word_exp(char **av, char *exp, t_token **t, int *idx)
{
	char	**wildcard_expanded;
	int		i;

	if (exp[0] != '\0' && has_wildcard(exp))
	{
		wildcard_expanded = expand_wildcard(exp);
		free(exp);
		i = 0;
		while (wildcard_expanded && wildcard_expanded[i])
			av[(*idx)++] = wildcard_expanded[i++];
		if (wildcard_expanded)
			free(wildcard_expanded);
		*t = (*t)->next;
		return (0);
	}
	if (exp[0] != '\0')
		av[(*idx)++] = exp;
	else
		free(exp);
	*t = (*t)->next;
	return (0);
}
