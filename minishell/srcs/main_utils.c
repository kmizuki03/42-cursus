/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 18:03:22 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:06:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*prepare_tokens(char *input, t_shell *shell)
{
	t_token	*tokens;
	int		i;

	if (!input || !*input)
		return (NULL);
	add_history(input);
	reset_syntax_error_flag(shell);
	tokens = tokenize(input);
	if (!tokens)
	{
		i = 0;
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (input[i] != '\0' && input[i] != '#')
			shell->last_exit_status = 2;
	}
	return (tokens);
}

static void	execute_parsed_ast(t_token *tokens, t_shell *shell)
{
	t_ast	*ast;
	int		saved_status;

	saved_status = shell->last_exit_status;
	ast = parse_ast(tokens, shell);
	free_tokens(tokens);
	if (!ast)
	{
		if (shell->last_exit_status == saved_status)
			shell->last_exit_status = 2;
		return ;
	}
	shell->last_exit_status = execute_ast(ast, shell);
	free_ast(ast);
}

void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;

	tokens = prepare_tokens(input, shell);
	if (!tokens)
		return ;
	execute_parsed_ast(tokens, shell);
}
