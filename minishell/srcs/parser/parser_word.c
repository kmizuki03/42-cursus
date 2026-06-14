/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:03:22 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:03:22 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_quoted_word(char *expanded, char **av, int *idx)
{
	if (expanded[0] != '\0')
		av[(*idx)++] = expanded;
	else
		free(expanded);
	return (0);
}

static int	handle_unquoted_word(char *expanded, char **av, int *idx)
{
	char	**words;
	int		i;

	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (-1);
	i = 0;
	while (words[i])
		av[(*idx)++] = words[i++];
	free(words);
	return (0);
}

int	handle_word_token(t_token **tokens, char **av, int *idx, t_shell *shell)
{
	char	*expanded;

	expanded = expand_tilde_token((*tokens)->value, shell);
	if (!expanded)
		return (-1);
	if (is_token_quoted((*tokens)->value))
	{
		if (handle_quoted_word(expanded, av, idx) == -1)
			return (-1);
	}
	else
	{
		if (handle_unquoted_word(expanded, av, idx) == -1)
			return (-1);
	}
	*tokens = (*tokens)->next;
	return (0);
}
