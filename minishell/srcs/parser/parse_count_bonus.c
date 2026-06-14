/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:03:22 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:06:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	count_quoted_token(t_token *token, t_shell *shell)
{
	char	*expanded;
	char	**exp;

	if (!is_word_with_wildcard(token))
		return (1);
	expanded = expand_variables(token->value, shell);
	if (expanded)
	{
		exp = expand_wildcard(expanded);
		free(expanded);
		if (exp)
			return (count_wildcard_matches(exp));
		return (1);
	}
	return (1);
}

static int	count_wildcard_in_word(char *word)
{
	char	**wildcard_exp;
	int		count;

	wildcard_exp = expand_wildcard(word);
	if (wildcard_exp)
	{
		count = count_wildcard_matches(wildcard_exp);
		return (count);
	}
	return (1);
}

static int	count_unquoted_token(char *expanded, t_shell *shell)
{
	char	**words;
	int		count;
	int		i;

	(void)shell;
	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (1);
	count = 0;
	i = 0;
	while (words[i])
	{
		if (has_wildcard(words[i]))
			count += count_wildcard_in_word(words[i]);
		else if (words[i][0] != '\0')
			count++;
		i++;
	}
	free_array(words);
	return (count);
}

int	count_word_token(t_token *token, t_shell *shell)
{
	char	*expanded;

	if (is_quoted_str(token->value))
		return (count_quoted_token(token, shell));
	expanded = expand_variables(token->value, shell);
	if (!expanded || expanded[0] == '\0')
	{
		if (expanded)
			free(expanded);
		return (0);
	}
	return (count_unquoted_token(expanded, shell));
}
