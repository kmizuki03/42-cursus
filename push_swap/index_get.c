/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:49:25 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:49:26 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_index(t_stack *stack)
{
	int	min;

	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}

int	get_max_index(t_stack *stack)
{
	int	max;

	max = stack->index;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	get_position(t_stack *stack, int index)
{
	int	position;

	position = 0;
	while (stack)
	{
		if (stack->index == index)
			return (position);
		position++;
		stack = stack->next;
	}
	return (-1);
}

int	get_index_at_pos(t_stack *stack, int pos)
{
	int	i;

	i = 0;
	while (stack && i < pos)
	{
		stack = stack->next;
		i++;
	}
	if (stack)
		return (stack->index);
	return (-1);
}

int	get_target_index(t_stack *stack_b, int index_a)
{
	int		target;
	t_stack	*tmp;

	target = INT_MIN;
	tmp = stack_b;
	while (tmp)
	{
		if (tmp->index < index_a && tmp->index > target)
			target = tmp->index;
		tmp = tmp->next;
	}
	if (target == INT_MIN)
		return (get_max_index(stack_b));
	return (target);
}
