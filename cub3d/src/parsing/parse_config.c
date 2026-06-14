/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:12 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:28:12 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	trim_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}

static int	get_tex_index(char *key)
{
	if (ft_strcmp(key, "NO") == 0)
		return (TEX_NORTH);
	if (ft_strcmp(key, "SO") == 0)
		return (TEX_SOUTH);
	if (ft_strcmp(key, "WE") == 0)
		return (TEX_WEST);
	if (ft_strcmp(key, "EA") == 0)
		return (TEX_EAST);
	return (-1);
}

static int	set_config(t_game *game, char *key, char *val)
{
	int	idx;

	idx = get_tex_index(key);
	if (idx >= 0)
		return (set_texture(game, idx, val));
	if (ft_strcmp(key, "F") == 0)
		return (set_color(&game->config.floor,
				&game->config.floor_set, val));
	if (ft_strcmp(key, "C") == 0)
		return (set_color(&game->config.ceiling,
				&game->config.ceiling_set, val));
	return (-1);
}

static int	identify_config(t_game *game, char *line)
{
	char	**tokens;
	int		ret;
	int		i;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (-1);
	ret = 1;
	if (!tokens[0] || tokens[0][0] == '\n')
		ret = 0;
	else
	{
		trim_newline(tokens[1]);
		if (set_config(game, tokens[0], tokens[1]) != 0)
			ret = -1;
	}
	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
	return (ret);
}

int	parse_config(t_game *game, int fd)
{
	char	*line;
	int		count;
	int		status;

	count = 0;
	while (count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (1);
		status = identify_config(game, line);
		free(line);
		if (status == -1)
			return (1);
		if (status == 1)
			count++;
	}
	return (0);
}
