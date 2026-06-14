/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:02 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/14 23:15:18 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	collect_pipe_cmds(t_ast *ast, t_cmd **list)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD && ast->cmd)
	{
		ast->cmd->next = *list;
		*list = ast->cmd;
		return ;
	}
	if (ast->type == NODE_PIPE)
	{
		collect_pipe_cmds(ast->right, list);
		collect_pipe_cmds(ast->left, list);
	}
}

static void	clear_cmd_links(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD && ast->cmd)
		ast->cmd->next = NULL;
	if (ast->type == NODE_PIPE)
	{
		clear_cmd_links(ast->left);
		clear_cmd_links(ast->right);
	}
}

static int	execute_pipe_node(t_ast *ast, t_shell *shell)
{
	t_cmd	*pipeline;
	int		status;

	pipeline = NULL;
	collect_pipe_cmds(ast, &pipeline);
	if (!pipeline)
		return (1);
	status = execute_pipeline(pipeline, shell);
	clear_cmd_links(ast);
	return (status);
}

static int	execute_logical_node(t_ast *ast, t_shell *shell)
{
	int	status;

	if (ast->type == NODE_AND)
	{
		status = execute_ast(ast->left, shell);
		if (status == 0)
			return (execute_ast(ast->right, shell));
		return (status);
	}
	if (ast->type == NODE_OR)
	{
		status = execute_ast(ast->left, shell);
		if (status != 0)
			return (execute_ast(ast->right, shell));
		return (status);
	}
	if (ast->type == NODE_BACKGROUND)
	{
		execute_ast(ast->left, shell);
		return (execute_ast(ast->right, shell));
	}
	return (0);
}

int	execute_ast(t_ast *ast, t_shell *shell)
{
	if (!ast)
		return (0);
	if (ast->type == NODE_CMD)
		return (execute(ast->cmd, shell));
	if (ast->type == NODE_PIPE)
		return (execute_pipe_node(ast, shell));
	if (ast->type == NODE_SUBSHELL)
		return (execute_subshell(ast, shell));
	return (execute_logical_node(ast, shell));
}
