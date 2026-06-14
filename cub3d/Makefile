
NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes -I minilibx-linux

MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/init.c \
			  $(SRC_DIR)/cleanup.c \
			  $(SRC_DIR)/graphics/mlx_utils.c \
			  $(SRC_DIR)/graphics/render.c \
			  $(SRC_DIR)/graphics/texture.c \
			  $(SRC_DIR)/raycasting/raycast.c \
			  $(SRC_DIR)/raycasting/dda.c \
			  $(SRC_DIR)/raycasting/draw.c \
			  $(SRC_DIR)/input/key_handler.c \
			  $(SRC_DIR)/input/movement.c \
			  $(SRC_DIR)/input/hooks.c \
			  $(SRC_DIR)/parsing/parse_main.c \
			  $(SRC_DIR)/parsing/parse_map.c \
			  $(SRC_DIR)/parsing/map_utils.c \
			  $(SRC_DIR)/parsing/parse_utils.c \
			  $(SRC_DIR)/parsing/ft_string.c \
			  $(SRC_DIR)/parsing/parse_config.c \
			  $(SRC_DIR)/parsing/parse_color.c \
			  $(SRC_DIR)/parsing/validate_map.c

OBJS		= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX) $(NAME)

$(MLX):
	@make -C $(MLX_DIR) 2>/dev/null

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/cub3d.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
