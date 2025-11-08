/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:50:46 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:50:46 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_value_pos(t_stack *stack)
{
	int	max;
	int	pos;
	int	max_pos;

	max = stack->value;
	pos = 0;
	max_pos = 0;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_pos = pos;
		}
		pos++;
		stack = stack->next;
	}
	return (max_pos);
}

void	sort_three(t_stack **stack_a)
{
	int	max_pos;

	if (is_sorted(*stack_a))
		return ;
	max_pos = get_max_value_pos(*stack_a);
	if (max_pos == 0)
		ra(stack_a, 1);
	else if (max_pos == 1)
		rra(stack_a, 1);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}
