/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:48 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:49 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static void	free_redirs(t_redir *redirs)
{
	t_redir	*tmp;

	while (redirs)
	{
		tmp = redirs;
		redirs = redirs->next;
		if (tmp->file)
			free(tmp->file);
		if (tmp->heredoc_fd != -1)
			close(tmp->heredoc_fd);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->av)
		free_array(cmd->av);
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	free(cmd);
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free_cmd(tmp);
	}
}
