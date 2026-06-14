/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:00:00 by kato              #+#    #+#             */
/*   Updated: 2025/05/09 01:10:00 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_exit(char *message)
{
	write(2, "Error: ", 7);
	while (*message)
	{
		write(2, message, 1);
		message++;
	}
	write(2, "\n", 1);
	exit(1);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
		result += ft_atof_fraction(++str);
	return (result * sign);
}

double	ft_atof_fraction(const char *str)
{
	double	fraction;
	double	result;

	fraction = 0.1;
	result = 0.0;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str - '0') * fraction;
		fraction *= 0.1;
		str++;
	}
	return (result);
}

void	print_usage(void)
{
	write(1, "Usage: ./fractol <fractal_type> [julia_re julia_im]\n", 52);
	write(1, "Fractal types:\n", 14);
	write(1, "  mandelbrot\n", 13);
	write(1, "  julia <re> <im>\n", 18);
	write(1, "\nControls:\n", 11);
	write(1, "  Arrow keys: Move\n", 18);
	write(1, "  Mouse wheel: Zoom\n", 19);
	write(1, "  ESC: Exit\n", 12);
	exit(1);
}
