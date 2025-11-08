/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:00:00 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/29 18:57:39 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}					t_stack;

typedef struct s_rotate_params
{
	int	pos_a;
	int	pos_b;
	int	size_a;
	int	size_b;
}		t_rotate_params;

t_stack				*stack_new(int value);
void				stack_add_back(t_stack **stack, t_stack *new);
t_stack				*stack_last(t_stack *stack);
int					stack_size(t_stack *stack);
void				free_stack(t_stack **stack);

void				sa(t_stack **stack_a, int print);
void				sb(t_stack **stack_b, int print);
void				ss(t_stack **stack_a, t_stack **stack_b, int print);
void				pa(t_stack **stack_a, t_stack **stack_b, int print);
void				pb(t_stack **stack_a, t_stack **stack_b, int print);

void				ra(t_stack **stack_a, int print);
void				rb(t_stack **stack_b, int print);
void				rr(t_stack **stack_a, t_stack **stack_b, int print);
void				rra(t_stack **stack_a, int print);
void				rrb(t_stack **stack_b, int print);
void				rrr(t_stack **stack_a, t_stack **stack_b, int print);

void				parse_args(int argc, char **argv, t_stack **stack_a);
int					has_duplicates(t_stack *stack);

void				index_stack(t_stack **stack);
int					get_min_index(t_stack *stack);
int					get_max_index(t_stack *stack);
int					get_position(t_stack *stack, int index);
int					get_target_index(t_stack *stack_b, int index_a);
int					get_index_at_pos(t_stack *stack, int pos);

void				sort_three(t_stack **stack_a);
void				sort_small(t_stack **stack_a, t_stack **stack_b);
void				turk_sort(t_stack **a, t_stack **b);

void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
int					ft_strlen(const char *s);
int					is_number(char *str);
int					is_sorted(t_stack *stack);
void				error_exit(t_stack **stack_a, t_stack **stack_b);
char				**ft_split(char const *s, char c);
void				free_string_array(char **arr);

#endif
