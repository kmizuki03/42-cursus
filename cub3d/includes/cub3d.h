/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 13:28:51 by kato              #+#    #+#             */
/*   Updated: 2026/05/23 13:29:59 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define WIN_TITLE "cub3D"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_DESTROY 17

# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define MAP_EMPTY '0'
# define MAP_WALL '1'
# define MAP_SPACE ' '

# define ERR_USAGE "Error\nUsage: ./cub3D <map.cub>\n"
# define ERR_FILE "Error\nCannot open file\n"
# define ERR_FORMAT "Error\nInvalid file format\n"
# define ERR_MAP "Error\nInvalid map\n"
# define ERR_TEXTURE "Error\nCannot load texture\n"
# define ERR_COLOR "Error\nInvalid color format\n"
# define ERR_PLAYER "Error\nPlayer not found or multiple players\n"
# define ERR_MLX "Error\nMLX initialization failed\n"
# define ERR_MALLOC "Error\nMemory allocation failed\n"

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3
# define TEX_COUNT 4

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

typedef struct s_player
{
	t_vec2d	pos;
	t_vec2d	dir;
	t_vec2d	plane;
}	t_player;

typedef struct s_ray
{
	t_vec2d	dir;
	t_vec2d	side_dist;
	t_vec2d	delta_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_config
{
	char	*tex_path[TEX_COUNT];
	t_color	floor;
	t_color	ceiling;
	int		floor_set;
	int		ceiling_set;
	int		tex_set[TEX_COUNT];
}	t_config;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		textures[TEX_COUNT];
	t_player	player;
	t_map		map;
	t_config	config;
	t_keys		keys;
}	t_game;

int		init_mlx(t_game *game);
void	img_pixel_put(t_img *img, int x, int y, int color);
int		img_pixel_get(t_img *img, int x, int y);
int		create_image(t_game *game, t_img *img, int width, int height);

int		render_frame(t_game *game);
void	draw_ceiling_floor(t_game *game);

int		load_textures(t_game *game);
int		get_tex_color(t_img *tex, int x, int y);

void	perform_raycasting(t_game *game);

void	init_ray(t_game *game, t_ray *ray, int x);
void	calc_step_and_side_dist(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	calc_wall_dist(t_game *game, t_ray *ray);

void	draw_wall_stripe(t_game *game, t_ray *ray, int x);
int		get_wall_tex_index(t_ray *ray);

int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	process_movement(t_game *game);

int		setup_hooks(t_game *game);
int		close_window(t_game *game);
int		game_loop(t_game *game);

int		init_game(t_game *game);
void	init_player(t_player *player, double x, double y, char dir);

int		parse_cub_file(t_game *game, const char *filename);

void	cleanup_game(t_game *game);
void	free_map(t_map *map);
void	free_config(t_config *config);

int		rgb_to_int(t_color color);
int		ft_error(char *msg);

int		parse_cub_file(t_game *game, const char *filename);
int		parse_config(t_game *game, int fd);
int		parse_map(t_game *game, int fd);
int		validate_map(t_game *game);

void	trim_newline(char *str);
int		set_texture(t_game *game, int idx, char *val);
int		set_color(t_color *color, int *set, char *val);

char	*read_map_lines(int fd);
int		has_internal_empty_line(const char *s);
void	measure_map(t_map *map);
int		pad_map(t_map *map);

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);
#endif
