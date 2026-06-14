/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:31 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:32 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	validate_redir_target(t_token **tok, t_shell *sh)
{
	char	*err_token;

	if (*tok && (*tok)->type == TOKEN_WORD)
		return (0);
	err_token = NULL;
	if (*tok)
	{
		if ((*tok)->type == TOKEN_BACKGROUND)
			err_token = "&";
		else
			err_token = get_token_str((*tok)->type);
	}
	print_syntax_error(err_token, sh);
	return (-1);
}

static int	is_heredoc_quoted(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == 1 || value[i] == 2 || value[i] == 3 || value[i] == 4)
			return (1);
		i++;
	}
	return (0);
}

static int	add_heredoc_redir(t_redir *redir, int quoted, t_shell *sh)
{
	if (handle_heredoc(redir, quoted, sh) == -1)
	{
		sh->last_exit_status = 130;
		free(redir->file);
		if (redir->heredoc_fd != -1)
			close(redir->heredoc_fd);
		free(redir);
		return (-1);
	}
	return (0);
}

static int	append_redir(t_token **tok, t_cmd *cmd, t_redir *redir)
{
	add_redir(cmd, redir);
	*tok = (*tok)->next;
	return (0);
}

int	parse_redir_token(t_token **tok, t_cmd *cmd, char **av, t_shell *sh)
{
	t_redir_type	type;
	char			*filename;
	t_redir			*redir;
	int				quoted;

	(void)av;
	type = token_to_redir_type((*tok)->type);
	*tok = (*tok)->next;
	if (validate_redir_target(tok, sh) == -1)
		return (-1);
	quoted = is_heredoc_quoted((*tok)->value);
	filename = get_redir_filename_bonus(tok, sh, type);
	if (!filename)
		return (-1);
	redir = new_redir(type, filename);
	if (free(filename), !redir)
		return (-1);
	if (type == REDIR_HEREDOC && add_heredoc_redir(redir, quoted, sh) == -1)
		return (-1);
	return (append_redir(tok, cmd, redir));
}
