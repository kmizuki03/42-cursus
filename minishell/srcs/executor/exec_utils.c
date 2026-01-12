/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:06 by kmizuki           #+#    #+#             */
/*   Updated: 2025/11/10 23:18:07 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fds(t_shell *shell)
{
	dup2(shell->stdin_backup, STDIN_FILENO);
	dup2(shell->stdout_backup, STDOUT_FILENO);
}

int	print_brace_error(int open)
{
	if (open)
		print_error(NULL, NULL, "syntax error: unexpected end of file");
	else
		print_error(NULL, NULL, "syntax error near unexpected token `}'");
	return (2);
}

void	handle_command_not_found(char *cmd_name)
{
	struct stat	st;

	if (ft_strchr(cmd_name, '/'))
	{
		if (access(cmd_name, F_OK) == 0)
		{
			if (stat(cmd_name, &st) == 0 && S_ISDIR(st.st_mode))
			{
				print_error(cmd_name, NULL, "Is a directory");
				exit(126);
			}
			print_error(cmd_name, NULL, "Permission denied");
			exit(126);
		}
		print_error(cmd_name, NULL, "No such file or directory");
		exit(127);
	}
	print_error(cmd_name, NULL, "command not found");
	exit(127);
}

int	handle_empty_cmd(t_cmd *cmd, t_shell *shell)
{
	if (cmd->redirs)
	{
		if (setup_redirections(cmd->redirs, shell) == -1)
		{
			restore_std_fds(shell);
			return (1);
		}
		restore_std_fds(shell);
	}
	return (0);
}

void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**envp;
	struct stat	st;

	if (!cmd->av || !cmd->av[0])
		exit(0);
	path = find_command_path(cmd->av[0], shell->env);
	if (!path)
		handle_command_not_found(cmd->av[0]);
	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		print_error(cmd->av[0], NULL, "Is a directory");
		free(path);
		exit(126);
	}
	envp = env_to_array(shell->env);
	if (!envp)
		exit(1);
	if (execve(path, cmd->av, envp) == -1)
	{
		print_error(cmd->av[0], NULL, strerror(errno));
		free(path);
		free_array(envp);
		exit(126);
	}
}
