/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 02:32:47 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:03:22 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->av = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*new_redir(t_redir_type type, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->heredoc_fd = -1;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

static int	count_word_token(t_token *token, t_shell *shell)
{
	char	*expanded;
	char	**words;
	int		count;

	if (is_token_quoted(token->value))
		return (1);
	expanded = expand_tilde_token(token->value, shell);
	if (!expanded || expanded[0] == '\0')
	{
		if (expanded)
			free(expanded);
		return (0);
	}
	words = ft_split(expanded, ' ');
	free(expanded);
	if (!words)
		return (1);
	count = 0;
	while (words[count])
		count++;
	free_array(words);
	return (count);
}

int	count_args(t_token *tokens, t_shell *shell)
{
	int	count;

	count = 0;
	while (tokens && tokens->type != TOKEN_PIPE && tokens->type != TOKEN_AND
		&& tokens->type != TOKEN_OR && tokens->type != TOKEN_RPAREN)
	{
		if (tokens->type == TOKEN_WORD)
			count += count_word_token(tokens, shell);
		else if (is_redir_token(tokens->type) && tokens->next)
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (count);
}
