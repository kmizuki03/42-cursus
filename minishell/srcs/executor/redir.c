/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:15 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:16 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_and_dup(char *file, int flags, int target_fd)
{
	int	fd;

	if (flags == O_RDONLY)
		fd = open(file, flags);
	else
		fd = open(file, flags, 0644);
	if (fd == -1)
	{
		print_error(file, NULL, strerror(errno));
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		close(fd);
		print_error("dup2", NULL, strerror(errno));
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_file_redir(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open_and_dup(redir->file, O_RDONLY, STDIN_FILENO));
	else if (redir->type == REDIR_OUT)
		return (open_and_dup(redir->file,
				O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO));
	else if (redir->type == REDIR_APPEND)
		return (open_and_dup(redir->file,
				O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO));
	return (0);
}

static int	handle_redir_heredoc(t_redir *redir)
{
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		print_error("dup2", NULL, strerror(errno));
		return (-1);
	}
	close(redir->heredoc_fd);
	return (0);
}

int	setup_redirections(t_redir *redirs, t_shell *shell)
{
	int	ret;

	(void)shell;
	while (redirs)
	{
		if (redirs->type == REDIR_HEREDOC)
			ret = handle_redir_heredoc(redirs);
		else
			ret = handle_file_redir(redirs);
		if (ret == -1)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}
