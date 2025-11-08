/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_double_rotate(t_stack **a, t_stack **b, t_rotate_params *p);
void	exec_double_reverse(t_stack **a, t_stack **b, t_rotate_params *p);
void	exec_rotate_a(t_stack **a, t_rotate_params *p);
void	exec_rotate_b(t_stack **b, t_rotate_params *p);

static void	exec_all_rotations(t_stack **a, t_stack **b, t_rotate_params *p)
{
	exec_double_rotate(a, b, p);
	exec_double_reverse(a, b, p);
	exec_rotate_a(a, p);
	exec_rotate_b(b, p);
}

void	do_move(t_stack **a, t_stack **b, int pos_a)
{
	int				idx_a;
	t_rotate_params	p;

	idx_a = get_index_at_pos(*a, pos_a);
	p.pos_a = pos_a;
	p.pos_b = get_position(*b, get_target_index(*b, idx_a));
	p.size_a = stack_size(*a);
	p.size_b = stack_size(*b);
	exec_all_rotations(a, b, &p);
	pb(a, b, 1);
}
