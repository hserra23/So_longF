/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:19 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 14:56:18 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static void	check_texture_files(t_map *map)
{
	if (!check_file("imgs/wall.xpm"))
	{
		free_map(map->grid);
		error_exit("Error: Wall texture file not found\n");
	}
	if (!check_file("imgs/floor.xpm"))
	{
		free_map(map->grid);
		error_exit("Error: Floor texture file not found\n");
	}
	if (!check_file("imgs/player.xpm"))
	{
		free_map(map->grid);
		error_exit("Error: Player texture file not found\n");
	}
	if (!check_file("imgs/exit.xpm"))
	{
		free_map(map->grid);
		error_exit("Error: Exit texture file not found\n");
	}
	if (!check_file("imgs/collectible.xpm"))
	{
		free_map(map->grid);
		error_exit("Error: Collectible texture file not found\n");
	}
}

void	load_image(t_game *game, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->width,
			&img->height);
	if (!img->img)
	{
		ft_printf("Error: Failed to load texture: %s\n", path);
		close_game(game);
	}
}

void	load_textures(t_game *game)
{
	load_image(game, &game->img_wall, "imgs/wall.xpm");
	load_image(game, &game->img_floor, "imgs/floor.xpm");
	load_image(game, &game->img_player, "imgs/player.xpm");
	load_image(game, &game->img_collectible, "imgs/collectible.xpm");
	load_image(game, &game->img_exit, "imgs/exit.xpm");
}

int	init_game(t_game *game, char *map_file)
{
	game->map = parse_map(map_file);
	validate_map(&game->map);
	check_texture_files(&game->map);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_map(game->map.grid);
		error_exit("Error\nFailed to initialize MLX\n");
	}
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		free_map(game->map.grid);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		error_exit("Error\nFailed to create window\n");
	}
	load_textures(game);
	game->collected = 0;
	game->moves = 0;
	return (1);
}
