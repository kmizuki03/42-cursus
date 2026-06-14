/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:45 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:29:51 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	if (!map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
}

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (config->tex_path[i])
		{
			free(config->tex_path[i]);
			config->tex_path[i] = NULL;
		}
		i++;
	}
}

static void	destroy_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->textures[i].img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img);
			game->textures[i].img = NULL;
		}
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (game->mlx)
	{
		destroy_textures(game);
		if (game->screen.img)
		{
			mlx_destroy_image(game->mlx, game->screen.img);
			game->screen.img = NULL;
		}
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
	free_map(&game->map);
	free_config(&game->config);
}
