/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		push_initial(t_stack **a, t_stack **b, int size);
void	push_all_back(t_stack **a, t_stack **b, int pushed);
void	final_rotate(t_stack **a);
void	do_move(t_stack **a, t_stack **b, int pos_a);
int		calc_cost(t_stack *a, t_stack *b, int pos_a);
int		find_cheap(t_stack *a, t_stack *b);

void	turk_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	pushed;

	size = stack_size(*a);
	pushed = push_initial(a, b, size);
	size = stack_size(*a);
	while (size-- > 3)
	{
		do_move(a, b, find_cheap(*a, *b));
		pushed++;
	}
	sort_three(a);
	push_all_back(a, b, pushed);
	final_rotate(a);
}
