/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:35 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:15:18 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_cmd_tokens(t_token **tokens, t_cmd *cmd, char **av,
		t_shell *shell)
{
	int	idx;

	idx = 0;
	while (*tokens && (*tokens)->type != TOKEN_PIPE
		&& (*tokens)->type != TOKEN_AND && (*tokens)->type != TOKEN_OR
		&& (*tokens)->type != TOKEN_RPAREN && (*tokens)->type != TOKEN_EOF)
	{
		if (is_redir_token((*tokens)->type))
		{
			if (parse_redir_token(tokens, cmd, av, shell) == -1)
				return (-1);
		}
		else if ((*tokens)->type == TOKEN_WORD)
		{
			if (handle_word_token(tokens, av, &idx, shell) == -1)
				return (-1);
		}
		else
			*tokens = (*tokens)->next;
	}
	av[idx] = NULL;
	return (0);
}

t_cmd	*parse_single_cmd(t_token **tokens, t_shell *shell)
{
	t_cmd	*cmd;
	char	**av;
	int		count;
	int		j;

	cmd = new_cmd();
	if (!cmd)
		return (NULL);
	count = count_args(*tokens, shell);
	av = malloc(sizeof(char *) * (count + 1));
	if (!av)
		return (free_cmd(cmd), NULL);
	j = 0;
	while (j <= count)
		av[j++] = NULL;
	if (parse_cmd_tokens(tokens, cmd, av, shell) == -1)
		return (free_array(av), free_cmd(cmd), NULL);
	cmd->av = av;
	return (cmd);
}

t_cmd	*parse(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmds;
	t_cmd	*new;
	t_cmd	*tmp;

	if (!tokens)
		return (NULL);
	cmds = NULL;
	while (tokens)
	{
		new = parse_single_cmd(&tokens, shell);
		if (!new)
			return (free_cmds(cmds), NULL);
		if (!cmds)
			cmds = new;
		else
		{
			tmp = cmds;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (cmds);
}
