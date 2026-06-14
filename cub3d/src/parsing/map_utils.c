/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:27:54 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:30:41 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*read_map_lines(int fd)
{
	char	*all;
	char	*line;
	char	*tmp;

	all = ft_strdup("");
	if (!all)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(all, line);
		free(all);
		free(line);
		if (!tmp)
			return (NULL);
		all = tmp;
		line = get_next_line(fd);
	}
	return (all);
}

int	has_internal_empty_line(const char *s)
{
	int	i;
	int	started;
	int	empty_seen;

	i = 0;
	started = 0;
	empty_seen = 0;
	while (s[i])
	{
		if (s[i] != '\n')
		{
			if (empty_seen)
				return (1);
			started = 1;
		}
		else if (started && (i == 0 || s[i - 1] == '\n'))
			empty_seen = 1;
		i++;
	}
	return (0);
}

void	measure_map(t_map *map)
{
	int	y;
	int	len;

	y = 0;
	map->width = 0;
	while (map->grid[y])
	{
		len = (int)ft_strlen(map->grid[y]);
		if (len > map->width)
			map->width = len;
		y++;
	}
	map->height = y;
}

static char	*build_padded_row(char *src, int width)
{
	char	*row;
	int		x;
	int		len;

	row = malloc(width + 1);
	if (!row)
		return (NULL);
	len = (int)ft_strlen(src);
	x = 0;
	while (x < width)
	{
		if (x < len)
			row[x] = src[x];
		else
			row[x] = ' ';
		x++;
	}
	row[width] = '\0';
	return (row);
}

int	pad_map(t_map *map)
{
	int		y;
	char	*row;

	y = 0;
	while (y < map->height)
	{
		row = build_padded_row(map->grid[y], map->width);
		if (!row)
			return (1);
		free(map->grid[y]);
		map->grid[y] = row;
		y++;
	}
	return (0);
}
