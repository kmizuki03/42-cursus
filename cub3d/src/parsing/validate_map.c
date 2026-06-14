/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:25 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:30:54 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	flood_fill(t_game *game, int x, int y, char **visited)
{
	if (x < 0 || y < 0 || y >= game->map.height)
		return (1);
	if (x >= (int)ft_strlen(game->map.grid[y]))
		return (1);
	if (game->map.grid[y][x] == ' ' || game->map.grid[y][x] == '\0')
		return (1);
	if (game->map.grid[y][x] == '1' || visited[y][x] == 'V')
		return (0);
	visited[y][x] = 'V';
	if (flood_fill(game, x + 1, y, visited)
		|| flood_fill(game, x - 1, y, visited)
		|| flood_fill(game, x, y + 1, visited)
		|| flood_fill(game, x, y - 1, visited))
		return (1);
	return (0);
}

static char	**dup_grid(t_map *map)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * (map->height + 1));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		visited[i] = ft_strdup(map->grid[i]);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	visited[i] = NULL;
	return (visited);
}

int	validate_map(t_game *game)
{
	char	**visited;
	int		i;
	int		error;

	visited = dup_grid(&game->map);
	if (!visited)
		return (ft_error(ERR_MALLOC));
	error = flood_fill(game, (int)game->player.pos.x,
			(int)game->player.pos.y, visited);
	i = 0;
	while (visited[i])
		free(visited[i++]);
	free(visited);
	if (error)
		return (ft_error(ERR_MAP));
	return (0);
}
