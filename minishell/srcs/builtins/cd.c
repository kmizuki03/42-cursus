/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:17:27 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/15 23:43:11 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_cd_path(char **av, t_shell *shell, int *need_free)
{
	*need_free = 0;
	if (!av[1])
		return (get_home_path(shell));
	if (ft_strcmp(av[1], "-") == 0)
		return (get_oldpwd_path(shell));
	if (ft_strcmp(av[1], "..") == 0)
	{
		*need_free = 1;
		return (resolve_parent_path(shell));
	}
	if (av[2])
	{
		print_error("cd", NULL, "too many arguments");
		return (NULL);
	}
	return (av[1]);
}

static int	do_chdir(char **av, char *path, int need_free)
{
	char	*err_path;

	if (chdir(path) == -1)
	{
		if (av[1])
			err_path = av[1];
		else
			err_path = path;
		print_error("cd", err_path, strerror(errno));
		if (need_free)
			free(path);
		return (1);
	}
	if (need_free)
		free(path);
	return (0);
}

int	builtin_cd(char **av, t_shell *shell)
{
	char	*path;
	char	old_cwd[1024];
	char	new_cwd[1024];
	int		need_free;

	if (!getcwd(old_cwd, sizeof(old_cwd)))
		old_cwd[0] = '\0';
	path = get_cd_path(av, shell, &need_free);
	if (!path)
		return (1);
	if (do_chdir(av, path, need_free) == 1)
		return (1);
	if (old_cwd[0])
		set_env_value(&shell->env, "OLDPWD", old_cwd);
	if (getcwd(new_cwd, sizeof(new_cwd)))
		set_env_value(&shell->env, "PWD", new_cwd);
	return (0);
}
