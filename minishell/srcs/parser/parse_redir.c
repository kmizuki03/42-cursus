/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:31 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/19 19:49:04 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redir_target(t_token **tok, t_shell *sh)
{
	char	*err_token;

	if (!*tok || (*tok)->type != TOKEN_WORD)
	{
		err_token = NULL;
		if (*tok)
			err_token = get_token_str((*tok)->type);
		print_syntax_error(err_token, sh);
		return (-1);
	}
	return (0);
}

static int	is_redir_quoted(char *value)
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

static char	*get_redir_filename(t_token **tok, t_shell *sh, t_redir_type type)
{
	char	*filename;
	int		quoted;

	if (type == REDIR_HEREDOC)
		return (remove_markers((*tok)->value));
	quoted = is_redir_quoted((*tok)->value);
	filename = expand_variables((*tok)->value, sh);
	if (!filename)
		return (NULL);
	if (!quoted && is_ambiguous_redirect(filename))
	{
		print_error((*tok)->value, NULL, "ambiguous redirect");
		free(filename);
		sh->last_exit_status = 1;
		return (NULL);
	}
	return (filename);
}

int	parse_redir_token(t_token **tok, t_cmd *cmd, char **av, t_shell *sh)
{
	t_redir_type	type;
	char			*filename;
	t_redir			*redir;
	int				heredoc_quoted;

	(void)av;
	type = token_to_redir_type((*tok)->type);
	*tok = (*tok)->next;
	if (check_redir_target(tok, sh) == -1)
		return (-1);
	heredoc_quoted = is_redir_quoted((*tok)->value);
	filename = get_redir_filename(tok, sh, type);
	if (!filename)
		return (-1);
	redir = new_redir(type, filename);
	free(filename);
	if (!redir)
		return (-1);
	if (type == REDIR_HEREDOC && add_heredoc_redir(redir, heredoc_quoted, sh))
		return (-1);
	add_redir(cmd, redir);
	*tok = (*tok)->next;
	return (0);
}
