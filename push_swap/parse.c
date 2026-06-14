/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:49:38 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:49:39 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_duplicates(t_stack *stack)
{
	t_stack	*tmp;

	while (stack)
	{
		tmp = stack->next;
		while (tmp)
		{
			if (stack->value == tmp->value)
				return (1);
			tmp = tmp->next;
		}
		stack = stack->next;
	}
	return (0);
}

static int	check_overflow(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
		if (result * sign > INT_MAX || result * sign < INT_MIN)
			return (1);
	}
	return (0);
}

static void	parse_string_arg(char *str, t_stack **stack_a)
{
	char	**split;
	int		i;
	t_stack	*new;

	split = ft_split(str, ' ');
	if (!split)
		error_exit(stack_a, NULL);
	i = 0;
	while (split[i])
	{
		if (!is_number(split[i]) || check_overflow(split[i]))
		{
			free_string_array(split);
			error_exit(stack_a, NULL);
		}
		new = stack_new(ft_atoi(split[i]));
		if (!new)
		{
			free_string_array(split);
			error_exit(stack_a, NULL);
		}
		stack_add_back(stack_a, new);
		i++;
	}
	free_string_array(split);
}

void	parse_args(int argc, char **argv, t_stack **stack_a)
{
	int		i;
	t_stack	*new;

	if (argc == 2)
		parse_string_arg(argv[1], stack_a);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (!is_number(argv[i]) || check_overflow(argv[i]))
				error_exit(stack_a, NULL);
			new = stack_new(ft_atoi(argv[i]));
			if (!new)
				error_exit(stack_a, NULL);
			stack_add_back(stack_a, new);
			i++;
		}
	}
	if (has_duplicates(*stack_a))
		error_exit(stack_a, NULL);
}
