/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:51:17 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rotate_vec(t_vec2d *v, double angle)
{
	double	old_x;

	old_x = v->x;
	v->x = v->x * cos(angle) - v->y * sin(angle);
	v->y = old_x * sin(angle) + v->y * cos(angle);
}

static void	rotate_player(t_game *game)
{
	if (game->keys.left)
	{
		rotate_vec(&game->player.dir, -ROT_SPEED);
		rotate_vec(&game->player.plane, -ROT_SPEED);
	}
	if (game->keys.right)
	{
		rotate_vec(&game->player.dir, ROT_SPEED);
		rotate_vec(&game->player.plane, ROT_SPEED);
	}
}

static void	move_forward_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	if (game->keys.w)
	{
		new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
		new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
		if (game->map.grid[(int)game->player.pos.y][(int)new_x] != MAP_WALL)
			game->player.pos.x = new_x;
		if (game->map.grid[(int)new_y][(int)game->player.pos.x] != MAP_WALL)
			game->player.pos.y = new_y;
	}
	if (game->keys.s)
	{
		new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
		new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
		if (game->map.grid[(int)game->player.pos.y][(int)new_x] != MAP_WALL)
			game->player.pos.x = new_x;
		if (game->map.grid[(int)new_y][(int)game->player.pos.x] != MAP_WALL)
			game->player.pos.y = new_y;
	}
}

static void	move_strafe(t_game *game)
{
	double	new_x;
	double	new_y;

	if (game->keys.a)
	{
		new_x = game->player.pos.x - game->player.plane.x * MOVE_SPEED;
		new_y = game->player.pos.y - game->player.plane.y * MOVE_SPEED;
		if (game->map.grid[(int)game->player.pos.y][(int)new_x] != MAP_WALL)
			game->player.pos.x = new_x;
		if (game->map.grid[(int)new_y][(int)game->player.pos.x] != MAP_WALL)
			game->player.pos.y = new_y;
	}
	if (game->keys.d)
	{
		new_x = game->player.pos.x + game->player.plane.x * MOVE_SPEED;
		new_y = game->player.pos.y + game->player.plane.y * MOVE_SPEED;
		if (game->map.grid[(int)game->player.pos.y][(int)new_x] != MAP_WALL)
			game->player.pos.x = new_x;
		if (game->map.grid[(int)new_y][(int)game->player.pos.x] != MAP_WALL)
			game->player.pos.y = new_y;
	}
}

void	process_movement(t_game *game)
{
	move_forward_backward(game);
	move_strafe(game);
	rotate_player(game);
}
