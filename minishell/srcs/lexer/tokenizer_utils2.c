/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:22 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:23 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_redir_type(char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
			return ((*i) += 2, TOKEN_REDIR_HEREDOC);
		return ((*i)++, TOKEN_REDIR_IN);
	}
	if (input[*i + 1] == '>')
		return ((*i) += 2, TOKEN_REDIR_APPEND);
	return ((*i)++, TOKEN_REDIR_OUT);
}

static t_token	*handle_redir(char *input, int *i)
{
	t_token_type	type;

	type = get_redir_type(input, i);
	return (new_token(type, NULL));
}

static t_token	*handle_pipe_or(char *input, int *i)
{
	if (input[*i + 1] == '|')
		return ((*i) += 2, new_token(TOKEN_OR, NULL));
	if (input[*i + 1] == '&')
	{
		print_syntax_error("|&", NULL);
		(*i) += 2;
		return (new_token(TOKEN_EOF, NULL));
	}
	return ((*i)++, new_token(TOKEN_PIPE, NULL));
}

static t_token	*handle_semicolon(int *i)
{
	print_syntax_error(";", NULL);
	(*i)++;
	return (new_token(TOKEN_EOF, NULL));
}

t_token	*handle_operator(char *input, int *i)
{
	if (input[*i] == ';')
		return (handle_semicolon(i));
	if (input[*i] == '|')
		return (handle_pipe_or(input, i));
	if (input[*i] == '&' && input[*i + 1] == '&')
		return ((*i) += 2, new_token(TOKEN_AND, NULL));
	if (input[*i] == '&')
		return ((*i)++, new_token(TOKEN_BACKGROUND, NULL));
	if (input[*i] == '(')
		return ((*i)++, new_token(TOKEN_LPAREN, NULL));
	if (input[*i] == ')')
		return ((*i)++, new_token(TOKEN_RPAREN, NULL));
	return (handle_redir(input, i));
}
