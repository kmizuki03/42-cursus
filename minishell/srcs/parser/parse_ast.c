/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:29 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:30 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*handle_binary_right(t_token **tok, t_shell *sh,
		t_ast *left, t_token_type op)
{
	t_ast		*node;
	t_node_type	n_type;

	*tok = (*tok)->next;
	n_type = NODE_PIPE;
	if (op != TOKEN_PIPE)
		n_type = NODE_AND;
	node = new_ast_node(n_type);
	if (!node)
		return (free_ast(left), NULL);
	node->left = left;
	node->right = parse_primary(tok, sh);
	if (!node->right)
	{
		print_syntax_error(get_op_token_str(tok), sh);
		return (free_ast(node), NULL);
	}
	return (node);
}

t_ast	*parse_binary_op(t_token **tok, t_shell *sh, t_token_type op)
{
	t_ast	*left;
	t_ast	*node;

	left = parse_primary(tok, sh);
	if (!left)
		return (NULL);
	while (*tok && (*tok)->type == op)
	{
		node = handle_binary_right(tok, sh, left, op);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}

static t_ast	*handle_control_op(t_token **curr, t_shell *shell,
		t_ast *left, t_node_type node_type)
{
	t_ast	*node;

	*curr = (*curr)->next;
	node = new_ast_node(node_type);
	if (!node)
		return (free_ast(left), NULL);
	node->left = left;
	node->right = parse_binary_op(curr, shell, TOKEN_PIPE);
	if (!node->right)
	{
		print_syntax_error(get_op_token_str(curr), shell);
		return (free_ast(node), NULL);
	}
	return (node);
}

t_ast	*parse_ast_ptr(t_token **tokens, t_shell *shell)
{
	t_ast	*left;
	t_ast	*node;

	if (!*tokens)
		return (NULL);
	if (check_initial_operator(*tokens))
		return (NULL);
	left = parse_binary_op(tokens, shell, TOKEN_PIPE);
	while (*tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR
			|| (*tokens)->type == TOKEN_BACKGROUND))
	{
		if ((*tokens)->type == TOKEN_AND)
			node = handle_control_op(tokens, shell, left, NODE_AND);
		else if ((*tokens)->type == TOKEN_OR)
			node = handle_control_op(tokens, shell, left, NODE_OR);
		else
			node = handle_control_op(tokens, shell, left, NODE_BACKGROUND);
		if (!node)
			return (NULL);
		left = node;
	}
	return (left);
}

t_ast	*parse_ast(t_token *tokens, t_shell *shell)
{
	t_token	*curr;

	curr = tokens;
	return (parse_ast_ptr(&curr, shell));
}
