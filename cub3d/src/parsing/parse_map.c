/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:03 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:30:47 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_map_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (!is_valid_map_char(map->grid[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	check_player(t_game *game, int x, int y, int *count)
{
	char	c;

	c = game->map.grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*count)++;
		if (*count > 1)
			return (1);
		init_player(&game->player, x, y, c);
		game->map.grid[y][x] = '0';
	}
	return (0);
}

static int	scan_players(t_game *game)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (check_player(game, x, y, &count))
				return (1);
			x++;
		}
		y++;
	}
	if (count == 0)
		return (1);
	return (0);
}

int	parse_map(t_game *game, int fd)
{
	char	*all_maps;

	all_maps = read_map_lines(fd);
	if (!all_maps)
		return (1);
	if (has_internal_empty_line(all_maps))
	{
		free(all_maps);
		return (1);
	}
	game->map.grid = ft_split(all_maps, '\n');
	free(all_maps);
	if (!game->map.grid)
		return (1);
	measure_map(&game->map);
	if (pad_map(&game->map) || check_map_chars(&game->map)
		|| scan_players(game))
	{
		free_map(&game->map);
		return (1);
	}
	return (0);
}
