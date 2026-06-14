/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:04 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 19:49:13 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin_parent(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (setup_redirections(cmd->redirs, shell) == -1)
	{
		restore_std_fds(shell);
		return (1);
	}
	status = execute_builtin(cmd->av, shell);
	restore_std_fds(shell);
	return (status);
}

static int	get_exit_status(int status)
{
	int	ret;

	ret = 1;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		ret = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		else if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
	}
	return (ret);
}

static void	redirect_stdin_if_needed(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		has_stdin_redir;
	int		null_fd;

	has_stdin_redir = 0;
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == REDIR_IN || redir->type == REDIR_HEREDOC)
			has_stdin_redir = 1;
		redir = redir->next;
	}
	if (!has_stdin_redir && !isatty(shell->stdin_backup))
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (null_fd != -1)
		{
			dup2(null_fd, STDIN_FILENO);
			close(null_fd);
		}
	}
}

static int	exec_in_fork(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	setup_parent_wait_signals();
	pid = fork();
	if (pid == -1)
	{
		restore_parent_signals();
		print_error("fork", NULL, strerror(errno));
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		if (setup_redirections(cmd->redirs, shell) == -1)
			exit(1);
		redirect_stdin_if_needed(cmd, shell);
		if (is_builtin(cmd->av[0]))
			exit(execute_builtin(cmd->av, shell));
		execute_external(cmd, shell);
	}
	(waitpid(pid, &status, 0), restore_parent_signals());
	return (get_exit_status(status));
}

int	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->av || !cmd->av[0])
		return (handle_empty_cmd(cmd, shell));
	if (ft_strcmp(cmd->av[0], "{") == 0)
		return (print_error(NULL, NULL, "unexpected end of file"), 2);
	if (ft_strcmp(cmd->av[0], "}") == 0)
		return (print_brace_error(0));
	if (ft_strcmp(cmd->av[0], ".") == 0 && !cmd->av[1])
	{
		print_error(".", NULL, "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		return (2);
	}
	if (is_builtin(cmd->av[0]) && !cmd->next)
		return (exec_builtin_parent(cmd, shell));
	return (exec_in_fork(cmd, shell));
}
