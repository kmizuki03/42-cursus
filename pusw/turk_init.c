/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_initial(t_stack **a, t_stack **b, int size)
{
	int	pushed;

	pushed = 0;
	if (size > 3)
	{
		pb(a, b, 1);
		pushed++;
	}
	if (size > 4)
	{
		pb(a, b, 1);
		pushed++;
	}
	return (pushed);
}
