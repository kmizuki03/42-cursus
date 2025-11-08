/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/19 14:28:53 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_pixel(t_fractal *f, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = f->addr + (y * f->line_length + x * (f->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_color(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0);
	t = (double)iter / (double)max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}

int	calculate_fractal(t_complex z, t_complex c, int max_iter)
{
	int		iter;
	double	tmp;

	iter = 0;
	while (iter < max_iter)
	{
		if (z.re * z.re + z.im * z.im > 4.0)
			return (iter);
		tmp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * tmp * z.im + c.im;
		iter++;
	}
	return (max_iter);
}

void	draw_line(t_fractal *f, int y)
{
	int			x;
	t_complex	c;
	t_complex	j;
	int			iter;

	x = 0;
	while (x < WIDTH)
	{
		c.re = (x - WIDTH / 2.0) / (0.5 * f->zoom * WIDTH) + f->offset_x;
		c.im = (y - HEIGHT / 2.0) / (0.5 * f->zoom * HEIGHT) + f->offset_y;
		if (f->type == 'm')
			iter = calculate_fractal((t_complex){0, 0}, c, f->max_iter);
		else if (f->type == 'j')
		{
			j.re = f->julia_re;
			j.im = f->julia_im;
			iter = calculate_fractal(c, j, f->max_iter);
		}
		put_pixel(f, x, y, get_color(iter, f->max_iter));
		x++;
	}
}
