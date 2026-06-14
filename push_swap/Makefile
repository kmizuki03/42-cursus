# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 12:00:00 by kmizuki           #+#    #+#              #
#    Updated: 2025/10/29 18:59:01 by kmizuki          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = push_swap.c stack.c commands_swap_push.c commands_push.c commands_rotate.c commands_reverse_rotate.c parse.c utils.c utils_atoi.c utils_split.c index_get.c index_set.c sort_three.c sort_small.c turk_cost.c turk_rotate1.c turk_rotate2.c turk_move.c turk_init.c turk_final.c turk_sort.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
