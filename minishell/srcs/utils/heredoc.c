/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:49 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 02:31:58 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*ret;
	char	*tmp;
	char	*var;
	int		i;

	ret = ft_strdup("");
	i = 0;
	while (line[i] && ret)
	{
		if (line[i] == '$' && line[i + 1])
		{
			var = expand_var(line, &i, shell);
			if (var)
				ret = join_parts(ret, var);
		}
		else
		{
			tmp = ft_substr(line, i, 1);
			ret = join_parts(ret, tmp);
			i++;
		}
	}
	return (ret);
}

static int	write_heredoc_line(char *line, t_heredoc_ctx *ctx)
{
	char	*expanded;

	if (ctx->expand)
	{
		expanded = expand_heredoc_line(line, ctx->shell);
		write(ctx->fd, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(ctx->fd, line, ft_strlen(line));
	write(ctx->fd, "\n", 1);
	free(line);
	return (0);
}

static int	process_heredoc_line(char *line, t_heredoc_ctx *ctx)
{
	if (!line)
	{
		ctx->eof_reached = 1;
		return (1);
	}
	if (ft_strcmp(line, ctx->delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (write_heredoc_line(line, ctx));
}

static int	heredoc_read_loop(t_heredoc_ctx *ctx, int stdin_copy)
{
	char	*line;
	char	*prompt;

	ctx->eof_reached = 0;
	prompt = NULL;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		prompt = "> ";
	while (1)
	{
		line = readline(prompt);
		if (g_signal == SIGINT)
		{
			free(line);
			dup2(stdin_copy, STDIN_FILENO);
			return (-1);
		}
		if (process_heredoc_line(line, ctx))
			break ;
	}
	return (0);
}

int	handle_heredoc(t_redir *redir, int quoted, t_shell *shell)
{
	int				pipe_fd[2];
	int				ret;
	int				stdin_copy;
	t_heredoc_ctx	ctx;

	if (pipe(pipe_fd) == -1)
		return (print_error("heredoc", NULL, strerror(errno)), -1);
	stdin_copy = dup(STDIN_FILENO);
	ctx.delimiter = redir->file;
	ctx.fd = pipe_fd[1];
	ctx.expand = !quoted;
	ctx.shell = shell;
	g_signal = 0;
	setup_heredoc_signals();
	ret = heredoc_read_loop(&ctx, stdin_copy);
	close(stdin_copy);
	setup_signals();
	close(pipe_fd[1]);
	if (ret == -1)
		return (close(pipe_fd[0]), -1);
	if (ctx.eof_reached)
		print_heredoc_warning(redir->file);
	redir->heredoc_fd = pipe_fd[0];
	return (0);
}
