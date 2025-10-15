/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:38:19 by hserra            #+#    #+#             */
/*   Updated: 2025/10/15 01:08:38 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_game *game, t_image *img, char *path)
{
	img ->img = mlx_xpm_file_to_image(game->mlx, path, &img->width, &img->height);
	if(!img->img)
	{
		ft_printf("Error: Failed to load textture: %s\n", path);
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
	game->mlx = mlx_init();
	if(!game->mlx)
		error_exit("Error: Failed to initialize MLX");
	game->map = parse_map(map_file);
	validate_map(&game->map);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE, game->map.height * TILE_SIZE, "so_long");
	if (!game->win)
	{
		free_map(game->map.grid);
		error_exit("Error: Failed to create window");
	}
	load_textures(game);
	game->collected = 0;
	game->moves = 0;
	return (1);
}