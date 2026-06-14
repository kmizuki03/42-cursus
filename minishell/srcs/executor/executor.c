/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:09 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:10 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute(t_cmd *cmds, t_shell *shell)
{
	int	status;

	if (!cmds)
		return (0);
	if (!cmds->next)
		status = execute_cmd(cmds, shell);
	else
		status = execute_pipeline(cmds, shell);
	return (status);
}
