# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kato <kato@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/10 00:00:00 by kmizuki           #+#    #+#              #
#    Updated: 2025/12/15 23:44:41 by kato             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
NAME_BONUS	= minishell_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I./includes
LIBS		= -lreadline

# Source directories
SRCS_DIR	= srcs
BUILTINS	= $(SRCS_DIR)/builtins
ENV			= $(SRCS_DIR)/env
EXECUTOR	= $(SRCS_DIR)/executor
LEXER		= $(SRCS_DIR)/lexer
PARSER		= $(SRCS_DIR)/parser
SIGNALS		= $(SRCS_DIR)/signals
UTILS		= $(SRCS_DIR)/utils
WILDCARD	= $(SRCS_DIR)/wildcard

# Object directories
OBJS_DIR	= objs
OBJS_BONUS_DIR = objs_bonus

# Source files (mandatory)
SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/main_utils.c \
			  $(BUILTINS)/builtin.c \
			  $(BUILTINS)/cd.c \
			  $(BUILTINS)/cd_utils.c \
			  $(BUILTINS)/echo.c \
			  $(BUILTINS)/env.c \
			  $(BUILTINS)/exit.c \
			  $(BUILTINS)/export.c \
			  $(BUILTINS)/export_utils.c \
			  $(BUILTINS)/pwd.c \
			  $(BUILTINS)/unset.c \
			  $(ENV)/env.c \
			  $(ENV)/env_init.c \
			  $(ENV)/env_utils.c \
			  $(ENV)/expand.c \
			  $(ENV)/expand_utils.c \
			  $(EXECUTOR)/exec_ast.c \
			  $(EXECUTOR)/exec_ast2.c \
			  $(EXECUTOR)/exec_cmd.c \
			  $(EXECUTOR)/exec_utils.c \
			  $(EXECUTOR)/executor.c \
			  $(EXECUTOR)/pipe.c \
			  $(EXECUTOR)/pipe_utils.c \
			  $(EXECUTOR)/redir.c \
			  $(LEXER)/token_utils.c \
			  $(LEXER)/tokenizer.c \
			  $(LEXER)/tokenizer_utils.c \
			  $(LEXER)/tokenizer_utils2.c \
			  $(PARSER)/ast_utils.c \
			  $(PARSER)/parse_ast.c \
			  $(PARSER)/parse_ast_utils.c \
			  $(PARSER)/parse_ast_utils2.c \
			  $(PARSER)/parse_redir.c \
			  $(PARSER)/parse_redir_utils.c \
			  $(PARSER)/parse_utils.c \
			  $(PARSER)/parse_tilde.c \
			  $(PARSER)/parser.c \
			  $(PARSER)/parser_word.c \
			  $(SIGNALS)/signals.c \
			  $(SIGNALS)/signals_utils.c \
			  $(UTILS)/error.c \
			  $(UTILS)/free.c \
			  $(UTILS)/heredoc.c \
			  $(UTILS)/heredoc_utils.c \
			  $(UTILS)/path.c \
			  $(UTILS)/utils.c \
			  $(UTILS)/utils_mem.c \
			  $(UTILS)/utils_split.c \
			  $(UTILS)/utils_str.c \
			  $(UTILS)/utils_strtoll.c

# Bonus source files
SRCS_BONUS	= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/main_utils.c \
			  $(BUILTINS)/builtin.c \
			  $(BUILTINS)/cd.c \
			  $(BUILTINS)/cd_utils.c \
			  $(BUILTINS)/echo.c \
			  $(BUILTINS)/env.c \
			  $(BUILTINS)/exit.c \
			  $(BUILTINS)/export.c \
			  $(BUILTINS)/export_utils.c \
			  $(BUILTINS)/pwd.c \
			  $(BUILTINS)/unset.c \
			  $(ENV)/env.c \
			  $(ENV)/env_init.c \
			  $(ENV)/env_utils.c \
			  $(ENV)/expand.c \
			  $(ENV)/expand_utils.c \
			  $(EXECUTOR)/exec_ast.c \
			  $(EXECUTOR)/exec_ast2.c \
			  $(EXECUTOR)/exec_cmd.c \
			  $(EXECUTOR)/exec_utils.c \
			  $(EXECUTOR)/executor.c \
			  $(EXECUTOR)/pipe.c \
			  $(EXECUTOR)/pipe_utils.c \
			  $(EXECUTOR)/redir.c \
			  $(LEXER)/token_utils.c \
			  $(LEXER)/tokenizer.c \
			  $(LEXER)/tokenizer_utils.c \
			  $(LEXER)/tokenizer_utils2.c \
			  $(PARSER)/ast_utils.c \
			  $(PARSER)/parse_ast.c \
			  $(PARSER)/parse_ast_utils.c \
			  $(PARSER)/parse_ast_utils2.c \
			  $(PARSER)/parse_redir_bonus.c \
			  $(PARSER)/parse_redir_utils.c \
			  $(PARSER)/parse_redir_utils_bonus.c \
			  $(PARSER)/parse_utils_bonus.c \
			  $(PARSER)/parse_utils2_bonus.c \
			  $(PARSER)/parse_tilde.c \
			  $(PARSER)/parse_count_bonus.c \
			  $(PARSER)/parser_bonus.c \
			  $(PARSER)/parser_word_bonus.c \
			  $(SIGNALS)/signals.c \
			  $(SIGNALS)/signals_utils.c \
			  $(UTILS)/error.c \
			  $(UTILS)/free.c \
			  $(UTILS)/heredoc.c \
			  $(UTILS)/heredoc_utils.c \
			  $(UTILS)/path.c \
			  $(UTILS)/utils.c \
			  $(UTILS)/utils_mem.c \
			  $(UTILS)/utils_split.c \
			  $(UTILS)/utils_str.c \
			  $(UTILS)/utils_strtoll.c \
			  $(WILDCARD)/wildcard_bonus.c \
			  $(WILDCARD)/wildcard_utils_bonus.c

# Object files
OBJS		= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
OBJS_BONUS	= $(SRCS_BONUS:$(SRCS_DIR)/%.c=$(OBJS_BONUS_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

# Compile mandatory objects
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile bonus objects
$(OBJS_BONUS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -DBONUS=1 -c $< -o $@

clean:
	rm -rf $(OBJS_DIR) $(OBJS_BONUS_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
