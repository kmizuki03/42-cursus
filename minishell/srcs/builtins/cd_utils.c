/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:45:00 by kato              #+#    #+#             */
/*   Updated: 2025/12/15 23:43:02 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_path(t_shell *shell)
{
	char	*path;

	path = get_env_value(shell->env, "HOME");
	if (!path)
	{
		print_error("cd", NULL, "HOME not set");
		return (NULL);
	}
	return (path);
}

char	*get_oldpwd_path(t_shell *shell)
{
	char	*path;

	path = get_env_value(shell->env, "OLDPWD");
	if (!path)
	{
		print_error("cd", NULL, "OLDPWD not set");
		return (NULL);
	}
	printf("%s\n", path);
	return (path);
}

char	*resolve_parent_path(t_shell *shell)
{
	char	*pwd;
	char	*last_slash;

	pwd = get_env_value(shell->env, "PWD");
	if (!pwd || !pwd[0])
		return (NULL);
	if (ft_strcmp(pwd, "/") == 0)
		return (ft_strdup("/"));
	last_slash = ft_strrchr(pwd, '/');
	if (!last_slash)
		return (NULL);
	if (last_slash == pwd)
		return (ft_strdup("/"));
	return (ft_substr(pwd, 0, last_slash - pwd));
}
