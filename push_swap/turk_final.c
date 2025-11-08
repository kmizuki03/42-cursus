/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_target_pos_in_a(t_stack *a, int index_b)
{
	int		target_idx;
	int		target_pos;
	t_stack	*tmp;

	target_idx = INT_MAX;
	tmp = a;
	while (tmp)
	{
		if (tmp->index > index_b && tmp->index < target_idx)
			target_idx = tmp->index;
		tmp = tmp->next;
	}
	if (target_idx == INT_MAX)
		target_pos = get_position(a, get_min_index(a));
	else
		target_pos = get_position(a, target_idx);
	return (target_pos);
}

static void	rotate_a_to_target(t_stack **a, int target_pos)
{
	int	size;

	size = stack_size(*a);
	if (target_pos <= size / 2)
	{
		while (target_pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (target_pos++ < size)
			rra(a, 1);
	}
}

static void	rotate_b_to_max(t_stack **b)
{
	int	pos;
	int	size;

	pos = get_position(*b, get_max_index(*b));
	size = stack_size(*b);
	while (pos > 0 && pos <= size / 2)
	{
		rb(b, 1);
		pos--;
	}
	while (pos < size && pos > size / 2)
	{
		rrb(b, 1);
		pos++;
	}
}

void	push_all_back(t_stack **a, t_stack **b, int pushed)
{
	int	max_idx_b;
	int	target_pos;

	while (pushed--)
	{
		max_idx_b = get_max_index(*b);
		target_pos = get_target_pos_in_a(*a, max_idx_b);
		rotate_a_to_target(a, target_pos);
		rotate_b_to_max(b);
		pa(a, b, 1);
	}
}

void	final_rotate(t_stack **a)
{
	int	pos;
	int	size;

	pos = get_position(*a, get_min_index(*a));
	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (pos++ < size)
			rra(a, 1);
	}
}
