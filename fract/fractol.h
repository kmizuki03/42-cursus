/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/19 14:23:01 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100

# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# define ZOOM_IN 4
# define ZOOM_OUT 5

typedef struct s_complex
{
	double	re;
	double	im;
}			t_complex;

typedef struct s_fractal
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	double	offset_x;
	double	offset_y;
	int		max_iter;
	char	type;
	double	julia_re;
	double	julia_im;
}			t_fractal;

void		init_fractal(t_fractal *f, char type);
void		init_mlx(t_fractal *f);
void		draw_fractal(t_fractal *f);
void		draw_line(t_fractal *f, int y);
void		put_pixel(t_fractal *f, int x, int y, int color);
int			get_color(int iter, int max_iter);
int			calculate_fractal(t_complex z, t_complex c, int max_iter);
int			handle_key(int keycode, t_fractal *f);
int			handle_mouse(int button, int x, int y, t_fractal *f);
int			handle_close(t_fractal *f);
void		handle_zoom(t_fractal *f, int button, int x, int y);
void		error_exit(char *message);
double		ft_atof(const char *str);
double		ft_atof_fraction(const char *str);
void		print_usage(void);

#endif
