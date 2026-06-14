/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 00:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/14 22:59:59 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*parse_subshell(t_token **tokens, t_shell *shell)
{
	t_ast	*node;
	t_ast	*inner;

	*tokens = (*tokens)->next;
	inner = parse_ast_ptr(tokens, shell);
	if (!*tokens || (*tokens)->type != TOKEN_RPAREN)
	{
		print_syntax_error(")", shell);
		free_ast(inner);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	node = new_ast_node(NODE_SUBSHELL);
	if (!node)
	{
		free_ast(inner);
		return (NULL);
	}
	node->left = inner;
	return (node);
}

static t_ast	*parse_simple_cmd(t_token **tokens, t_shell *shell)
{
	t_ast	*node;
	t_cmd	*cmd;

	cmd = parse_single_cmd(tokens, shell);
	if (!cmd)
		return (NULL);
	node = new_ast_node(NODE_CMD);
	if (!node)
		return (free_cmds(cmd), NULL);
	node->cmd = cmd;
	return (node);
}

t_ast	*parse_primary(t_token **tokens, t_shell *shell)
{
	if (!*tokens)
		return (NULL);
	if (is_operator_token((*tokens)->type))
		return (NULL);
	if ((*tokens)->type == TOKEN_LPAREN)
		return (parse_subshell(tokens, shell));
	return (parse_simple_cmd(tokens, shell));
}
