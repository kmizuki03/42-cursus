/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:11 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:12 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(int *pipe_fd)
{
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

void	setup_pipe_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

void	exec_in_child(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**envp;

	path = find_command_path(cmd->av[0], shell->env);
	if (!path)
	{
		print_error(cmd->av[0], NULL, "command not found");
		exit(127);
	}
	envp = env_to_array(shell->env);
	if (!envp)
		exit(1);
	if (execve(path, cmd->av, envp) == -1)
	{
		print_error(cmd->av[0], NULL, strerror(errno));
		exit(126);
	}
}

void	child_process(t_cmd *cmd, t_shell *shell, int in_fd, int out_fd)
{
	setup_child_signals();
	setup_pipe_fds(in_fd, out_fd);
	if (setup_redirections(cmd->redirs, shell) == -1)
		exit(1);
	if (!cmd->av || !cmd->av[0])
		exit(0);
	if (is_builtin(cmd->av[0]))
		exit(execute_builtin(cmd->av, shell));
	exec_in_child(cmd, shell);
}

int	get_out_fd(t_cmd *cur, int *pipe_fd)
{
	if (cur->next)
		return (pipe_fd[1]);
	return (STDOUT_FILENO);
}
