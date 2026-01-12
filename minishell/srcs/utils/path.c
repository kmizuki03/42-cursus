/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 23:18:51 by kmizuki           #+#    #+#             */
/*   Updated: 2025/12/18 02:58:23 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_access(char *path)
{
	struct stat	st;

	if (access(path, F_OK) == 0)
	{
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			return (NULL);
		if (access(path, X_OK) == 0)
			return (ft_strdup(path));
	}
	return (NULL);
}

static char	*search_in_paths(char *cmd, char **paths)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*ret;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (check_access(cmd));
	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	ret = search_in_paths(cmd, paths);
	free_array(paths);
	return (ret);
}
