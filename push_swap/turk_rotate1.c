/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_rotate1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_double_rotate(t_stack **a, t_stack **b, t_rotate_params *p)
{
	while (p->pos_a > 0 && p->pos_b > 0 && p->pos_a <= p->size_a / 2
		&& p->pos_b <= p->size_b / 2)
	{
		rr(a, b, 1);
		p->pos_a--;
		p->pos_b--;
	}
}

void	exec_double_reverse(t_stack **a, t_stack **b, t_rotate_params *p)
{
	while (p->pos_a < p->size_a && p->pos_b < p->size_b
		&& p->pos_a > p->size_a / 2 && p->pos_b > p->size_b / 2)
	{
		rrr(a, b, 1);
		p->pos_a++;
		p->pos_b++;
	}
}
