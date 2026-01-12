/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strtoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:48:09 by kato              #+#    #+#             */
/*   Updated: 2025/12/16 14:43:25 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_overflow_pos(long long r, int digit)
{
	if (r > LLONG_MAX / 10)
		return (1);
	if (r == LLONG_MAX / 10 && digit > LLONG_MAX % 10)
		return (1);
	return (0);
}

static int	check_overflow_neg(long long r, int digit)
{
	long long	limit;

	limit = -(LLONG_MIN / 10);
	if (r > limit)
		return (1);
	if (r == limit && digit > -(LLONG_MIN % 10))
		return (1);
	return (0);
}

static int	parse_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

int	ft_atoll(const char *s, long long *out)
{
	long long	r;
	int			sign;

	if (!s || !*s)
		return (1);
	while (ft_isspace(*s))
		s++;
	sign = parse_sign(&s);
	if (*s < '0' || *s > '9')
		return (1);
	r = 0;
	while (*s >= '0' && *s <= '9')
	{
		if (sign == 1 && check_overflow_pos(r, *s - '0'))
			return (1);
		if (sign == -1 && check_overflow_neg(r, *s - '0'))
			return (1);
		r = r * 10 + (*s++ - '0');
	}
	if (*s)
		return (1);
	*out = r * sign;
	return (0);
}
