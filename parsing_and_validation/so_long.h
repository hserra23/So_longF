/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:36:15 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 15:43:21 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/inc/ft_printf.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64

/* Key codes (may vary by OS - these are for Linux) */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307

/* Map elements */
# define WALL '1'
# define EMPTY '0'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

/* Structures */
typedef struct s_point
{
	int		x;
	int		y;
	int		size_x;
	int		size_y;
}			t_point;

typedef struct s_image
{
	void	*img;
	int		width;
	int		height;
}			t_image;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		players;
	t_point	player_pos;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_image	img_wall;
	t_image	img_floor;
	t_image	img_player;
	t_image	img_collectible;
	t_image	img_exit;
	int		collected;
	int		moves;
}			t_game;

/* Map validation */
int			check_rectangular(t_map *map);
int			check_walls(t_map *map);
int			check_valid_chars(t_map *map);
int			check_element_count(t_map *map);
int			validate_map(t_map *map);
int			is_unreachable(t_map *map, char **grid_copy, int x, int y);

/* Map parsing */
t_map		parse_map(char *filename);
int			validate_map(t_map *map);
void		free_map(char **map);

/* Game initialization */
int			init_game(t_game *game, char *map_file);
void		load_textures(t_game *game);

/* Rendering */
void		render_map(t_game *game);
void		render_tile(t_game *game, int x, int y);
void		put_image(t_game *game, t_image *img, int x, int y);

/* Player movement */
int			handle_keypress(int keycode, t_game *game);

/* Utils */
void		error_exit(char *message);
int			close_game(t_game *game);
int			ft_strlen(const char *str);
int			ft_strncmp(char *s1, char *s2, int n);
int			count_lines(char *filename);
int			get_map_width(char *filename);
char		**read_map_grid(char *filename, int height, int i);
int			check_valid_path(t_map *map);
void		flood_fill(char **grid_copy, int x, int y, t_map *map);
char		**copy_grid(t_map *map);
char		*get_next_line(int fd);

/* Game functions */
int			init_game(t_game *game, char *map_file);
void		load_textures(t_game *game);
void		render_map(t_game *game);
int			handle_keypress(int keycode, t_game *game);
void		move_player(t_game *game, int new_x, int new_y, int old_x);
int			close_game(t_game *game);

#endif