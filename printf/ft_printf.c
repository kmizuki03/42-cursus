/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:56:11 by kato              #+#    #+#             */
/*   Updated: 2025/07/21 22:20:15 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_putchar(char c);
int			ft_putstr(const char *s);
int			ft_putnbr(long n);
int			ft_putunbr(unsigned int n);
int			ft_puthex(unsigned long n, int upper);
int			ft_putptr(void *ptr);

static int	handle_format(char spec, va_list *args)
{
	if (spec == 'c')
		return (ft_putchar(va_arg(*args, int)));
	else if (spec == 's')
		return (ft_putstr(va_arg(*args, char *)));
	else if (spec == 'd' || spec == 'i')
		return (ft_putnbr(va_arg(*args, int)));
	else if (spec == 'u')
		return (ft_putunbr(va_arg(*args, unsigned int)));
	else if (spec == 'x')
		return (ft_puthex(va_arg(*args, unsigned int), 0));
	else if (spec == 'X')
		return (ft_puthex(va_arg(*args, unsigned int), 1));
	else if (spec == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (spec == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += handle_format(format[i], &args);
		}
		else
		{
			count += ft_putchar(format[i]);
		}
		i++;
	}
	va_end(args);
	if (count < 0)
		return (-1);
	return (count);
}
