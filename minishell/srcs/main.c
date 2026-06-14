/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:19:02 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/12 18:06:50 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	shell->last_exit_status = 0;
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	shell->syntax_error = 0;
}

static void	handle_signal_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		g_signal = 0;
	}
}

static int	handle_readline_input(t_shell *shell)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		if (g_signal == SIGINT)
		{
			g_signal = 0;
			return (1);
		}
		write(1, "exit\n", 5);
		return (0);
	}
	handle_signal_status(shell);
	process_input(input, shell);
	free(input);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	setup_signals();
	while (handle_readline_input(&shell))
		;
	free_env(shell.env);
	close(shell.stdin_backup);
	close(shell.stdout_backup);
	rl_clear_history();
	return (shell.last_exit_status);
}
