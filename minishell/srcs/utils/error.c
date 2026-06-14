/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:45 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/13 23:32:58 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_syntax_error_flag(t_shell *shell)
{
	if (shell)
		shell->syntax_error = 0;
}

int	has_syntax_error(t_shell *shell)
{
	if (shell)
		return (shell->syntax_error);
	return (0);
}

void	print_error(char *cmd, char *arg, char *msg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	exit_error(char *msg, int status)
{
	print_error(NULL, NULL, msg);
	exit(status);
}

void	print_syntax_error(char *token, t_shell *shell)
{
	if (shell && shell->syntax_error)
		return ;
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (token)
		write(2, token, ft_strlen(token));
	else
		write(2, "newline", 7);
	write(2, "'\n", 2);
	if (shell)
		shell->syntax_error = 1;
}
