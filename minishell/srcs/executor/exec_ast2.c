/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 23:14:59 by kato              #+#    #+#             */
/*   Updated: 2025/12/14 06:18:54 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_subshell(t_ast *ast, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", NULL, strerror(errno));
		return (1);
	}
	if (pid == 0)
	{
		status = execute_ast(ast->left, shell);
		exit(status);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (status);
}
