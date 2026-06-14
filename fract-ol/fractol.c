/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/05/09 01:57:27 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_fractal(t_fractal *f, char type)
{
	f->zoom = 1.0;
	f->offset_x = 0.0;
	f->offset_y = 0.0;
	f->max_iter = MAX_ITER;
	f->type = type;
	if (type == 'j')
	{
		f->julia_re = 0.285;
		f->julia_im = 0.01;
	}
}

void	init_mlx(t_fractal *f)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		error_exit("MLX initialization failed");
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
		error_exit("Window creation failed");
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		error_exit("Image creation failed");
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length,
			&f->endian);
}

int	main(int argc, char **argv)
{
	t_fractal	f;

	if (argc < 2 || argc > 4)
		print_usage();
	if (argv[1][0] == 'm')
		init_fractal(&f, 'm');
	else if (argv[1][0] == 'j')
	{
		if (argc != 4)
			print_usage();
		init_fractal(&f, 'j');
		f.julia_re = ft_atof(argv[2]);
		f.julia_im = ft_atof(argv[3]);
	}
	else
		print_usage();
	init_mlx(&f);
	mlx_hook(f.win, 2, 1L << 0, handle_key, &f);
	mlx_hook(f.win, 4, 1L << 2, handle_mouse, &f);
	mlx_hook(f.win, 17, 0, handle_close, &f);
	draw_fractal(&f);
	mlx_loop(f.mlx);
	return (0);
}
