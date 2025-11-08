/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/25 17:49:26 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	calc_moves(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

static int	get_max_cost(int cost_a, int cost_b)
{
	if (cost_a > cost_b)
		return (cost_a);
	return (cost_b);
}

static int	check_same_direction(int pos_a, int pos_b, int size_a, int size_b)
{
	int	both_forward;
	int	both_backward;

	both_forward = (pos_a <= size_a / 2 && pos_b <= size_b / 2);
	both_backward = (pos_a > size_a / 2 && pos_b > size_b / 2);
	return (both_forward || both_backward);
}

int	calc_cost(t_stack *a, t_stack *b, int pos_a)
{
	int	idx_a;
	int	pos_b;
	int	cost_a;
	int	cost_b;

	idx_a = get_index_at_pos(a, pos_a);
	pos_b = get_position(b, get_target_index(b, idx_a));
	cost_a = calc_moves(pos_a, stack_size(a));
	cost_b = calc_moves(pos_b, stack_size(b));
	if (check_same_direction(pos_a, pos_b, stack_size(a), stack_size(b)))
		return (get_max_cost(cost_a, cost_b));
	return (cost_a + cost_b);
}

int	find_cheap(t_stack *a, t_stack *b)
{
	int	size;
	int	cheap_pos;
	int	cheap_cost;
	int	i;
	int	cost;

	size = stack_size(a);
	cheap_pos = 0;
	cheap_cost = calc_cost(a, b, 0);
	i = 1;
	while (i < size)
	{
		cost = calc_cost(a, b, i);
		if (cost < cheap_cost)
		{
			cheap_cost = cost;
			cheap_pos = i;
		}
		i++;
	}
	return (cheap_pos);
}
