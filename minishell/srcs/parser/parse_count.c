/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/14 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_split_words(char *expanded)
{
	char	**words;
	int		count;

	if (!expanded || expanded[0] == '\0')
		return (0);
	words = ft_split(expanded, ' ');
	if (!words)
		return (1);
	count = 0;
	while (words[count])
		count++;
	free_array(words);
	return (count);
}

static int	count_unquoted_word(t_token *token, t_shell *shell)
{
	char	*expanded;
	int		count;

	expanded = expand_tilde_token(token->value, shell);
	if (!expanded)
		return (1);
	count = count_split_words(expanded);
	free(expanded);
	return (count);
}

int	count_args(t_token *tokens, t_shell *shell)
{
	int		count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE && tokens->type != TOKEN_AND
		&& tokens->type != TOKEN_OR && tokens->type != TOKEN_RPAREN)
	{
		if (tokens->type == TOKEN_WORD)
		{
			if (is_token_quoted(tokens->value))
				count++;
			else
				count += count_unquoted_word(tokens, shell);
		}
		else if (is_redir_token(tokens->type) && tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}
