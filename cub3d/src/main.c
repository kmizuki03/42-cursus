/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:29:59 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
	return (1);
}

int	rgb_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

static int	check_extension(const char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 4)
		return (0);
	if (filename[len - 4] == '.' && filename[len - 3] == 'c'
		&& filename[len - 2] == 'u' && filename[len - 1] == 'b')
		return (1);
	return (0);
}

static int	setup_game(t_game *game, char *path)
{
	if (parse_cub_file(game, path))
		return (1);
	if (init_mlx(game))
		return (1);
	if (load_textures(game))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_error(ERR_USAGE));
	if (!check_extension(argv[1]))
		return (ft_error(ERR_FORMAT));
	if (init_game(&game))
		return (1);
	if (setup_game(&game, argv[1]))
	{
		cleanup_game(&game);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
