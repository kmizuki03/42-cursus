/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:48 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:29:55 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		config->tex_path[i] = NULL;
		config->tex_set[i] = 0;
		i++;
	}
	config->floor.r = 0;
	config->floor.g = 0;
	config->floor.b = 0;
	config->ceiling.r = 0;
	config->ceiling.g = 0;
	config->ceiling.b = 0;
	config->floor_set = 0;
	config->ceiling_set = 0;
}

static void	set_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.y = -1;
		player->plane.x = 0.66;
	}
	else if (dir == 'S')
	{
		player->dir.y = 1;
		player->plane.x = -0.66;
	}
	else if (dir == 'E')
	{
		player->dir.x = 1;
		player->plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1;
		player->plane.y = -0.66;
	}
}

void	init_player(t_player *player, double x, double y, char dir)
{
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	set_direction(player, dir);
}

static void	init_game_fields(t_game *game)
{
	int	i;

	game->mlx = NULL;
	game->win = NULL;
	game->screen.img = NULL;
	game->screen.addr = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	i = 0;
	while (i < TEX_COUNT)
	{
		game->textures[i].img = NULL;
		game->textures[i].addr = NULL;
		i++;
	}
}

int	init_game(t_game *game)
{
	init_game_fields(game);
	init_config(&game->config);
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.dir.x = 0;
	game->player.dir.y = 0;
	game->player.plane.x = 0;
	game->player.plane.y = 0;
	return (0);
}
