/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:50:46 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:50:46 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_distance(t_stack *stack, int index)
{
	int	distance;

	distance = 0;
	while (stack)
	{
		if (stack->index == index)
			break ;
		distance++;
		stack = stack->next;
	}
	return (distance);
}

static void	rotate_to_min(t_stack **stack_a, int min_index, int size)
{
	int	distance;

	distance = get_distance(*stack_a, min_index);
	if (distance <= size / 2)
	{
		while ((*stack_a)->index != min_index)
			ra(stack_a, 1);
	}
	else
	{
		while ((*stack_a)->index != min_index)
			rra(stack_a, 1);
	}
}

static void	push_min_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	min_index;
	int	size;

	min_index = get_min_index(*stack_a);
	size = stack_size(*stack_a);
	rotate_to_min(stack_a, min_index, size);
	pb(stack_a, stack_b, 1);
}

void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b, 1);
}
