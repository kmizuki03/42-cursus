/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:49:25 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:49:26 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_next_min(t_stack *stack, int previous_min)
{
	int		min;
	t_stack	*tmp;

	min = INT_MAX;
	tmp = stack;
	while (tmp)
	{
		if (tmp->value > previous_min && tmp->value < min)
			min = tmp->value;
		tmp = tmp->next;
	}
	if (min == INT_MAX)
		return (previous_min);
	return (min);
}

static void	init_index(t_stack *stack)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp)
	{
		tmp->index = -1;
		tmp = tmp->next;
	}
}

static void	set_index_for_value(t_stack *stack, int min, int index)
{
	t_stack	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->value == min && tmp->index == -1)
		{
			tmp->index = index;
			break ;
		}
		tmp = tmp->next;
	}
}

void	index_stack(t_stack **stack)
{
	int	min;
	int	index;
	int	size;

	init_index(*stack);
	index = 0;
	min = INT_MIN;
	size = stack_size(*stack);
	while (index < size)
	{
		min = get_next_min(*stack, min);
		set_index_for_value(*stack, min, index);
		index++;
	}
}
