/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/14 00:00:00 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND
		|| type == TOKEN_OR || type == TOKEN_BACKGROUND);
}

char	*get_op_token_str(t_token **tok)
{
	if (*tok)
	{
		if ((*tok)->type == TOKEN_PIPE)
			return ("|");
		if ((*tok)->type == TOKEN_AND)
			return ("&&");
		if ((*tok)->type == TOKEN_OR)
			return ("||");
		if ((*tok)->type == TOKEN_BACKGROUND)
			return ("&");
	}
	return (NULL);
}

int	check_initial_operator(t_token *tokens)
{
	if (!is_operator_token(tokens->type))
		return (0);
	if (tokens->type == TOKEN_PIPE)
		print_syntax_error("|", NULL);
	else if (tokens->type == TOKEN_AND)
		print_syntax_error("&&", NULL);
	else if (tokens->type == TOKEN_OR)
		print_syntax_error("||", NULL);
	else if (tokens->type == TOKEN_BACKGROUND)
		print_syntax_error("&", NULL);
	return (1);
}
