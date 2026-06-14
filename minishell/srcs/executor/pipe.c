/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:21:09 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/11 22:23:44 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_last_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (0);
}

static int	wait_pipeline_pids(pid_t *pids, int count)
{
	int	status;
	int	last_status;
	int	i;

	last_status = 0;
	i = 0;
	while (i < count)
	{
		if (pids[i] != -1)
		{
			waitpid(pids[i], &status, 0);
			if (i == count - 1)
				last_status = status;
		}
		i++;
	}
	free(pids);
	return (get_last_exit_status(last_status));
}

static pid_t	fork_and_exec(t_cmd *cmd, t_shell *shell, int in_fd, int *pfd)
{
	pid_t	pid;
	int		out_fd;

	pid = fork();
	if (pid == -1)
	{
		print_error("fork", NULL, strerror(errno));
		return (-1);
	}
	if (pid == 0)
	{
		if (cmd->next)
			close(pfd[0]);
		out_fd = get_out_fd(cmd, pfd);
		child_process(cmd, shell, in_fd, out_fd);
	}
	return (pid);
}

static int	handle_pipe_step(t_cmd **cur, t_shell *sh, int *in, pid_t *pid)
{
	int		pipe_fd[2];

	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if ((*cur)->next && pipe(pipe_fd) == -1)
	{
		print_error("pipe", NULL, strerror(errno));
		return (-1);
	}
	*pid = fork_and_exec(*cur, sh, *in, pipe_fd);
	if (*pid == -1)
		return (close_pipe_fds(pipe_fd), -1);
	if (*in != STDIN_FILENO)
		close(*in);
	if ((*cur)->next)
	{
		close(pipe_fd[1]);
		*in = pipe_fd[0];
	}
	*cur = (*cur)->next;
	return (0);
}

int	execute_pipeline(t_cmd *cmds, t_shell *shell)
{
	int		in_fd;
	pid_t	*pids;
	t_cmd	*cur;
	int		i;
	int		count;

	count = 0;
	cur = cmds;
	while (cur && ++count)
		cur = cur->next;
	pids = malloc(sizeof(pid_t) * count);
	if (!pids)
		return (1);
	setup_parent_wait_signals();
	in_fd = STDIN_FILENO;
	cur = cmds;
	i = 0;
	while (i < count)
	{
		if (handle_pipe_step(&cur, shell, &in_fd, &pids[i++]) == -1)
			return (restore_parent_signals(), free(pids), 1);
	}
	restore_parent_signals();
	return (wait_pipeline_pids(pids, count));
}
