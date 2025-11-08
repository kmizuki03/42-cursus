/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_rotate2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_rotate_a(t_stack **a, t_rotate_params *p)
{
	while (p->pos_a > 0 && p->pos_a <= p->size_a / 2)
	{
		ra(a, 1);
		p->pos_a--;
	}
	while (p->pos_a < p->size_a && p->pos_a > p->size_a / 2)
	{
		rra(a, 1);
		p->pos_a++;
	}
}

void	exec_rotate_b(t_stack **b, t_rotate_params *p)
{
	while (p->pos_b > 0 && p->pos_b <= p->size_b / 2)
	{
		rb(b, 1);
		p->pos_b--;
	}
	while (p->pos_b < p->size_b && p->pos_b > p->size_b / 2)
	{
		rrb(b, 1);
		p->pos_b++;
	}
}
