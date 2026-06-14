/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:51:26 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	process_movement(game);
	render_frame(game);
	return (0);
}

int	setup_hooks(t_game *game)
{
	mlx_hook(game->win, X_EVENT_KEY_PRESS, 1L << 0,
		key_press, game);
	mlx_hook(game->win, X_EVENT_KEY_RELEASE, 1L << 1,
		key_release, game);
	mlx_hook(game->win, X_EVENT_DESTROY, 0,
		close_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	return (0);
}
