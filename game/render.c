/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:21:43 by hserra            #+#    #+#             */
/*   Updated: 2025/10/14 17:06:25 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_image(t_game *game, t_image *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img->img, x * TILE_SIZE, y * TILE_SIZE);
}

static void	render_tile(t_game *game, int x, int y)
{
	char tile;
	tile = game->map.grid[x][y];
	put_image(game, &game->img_floor, x, y);
	if (tile == WALL)
		put_image(game, &game->img_wall, x, y);
	else if (tile == COLLECTIBLE)
		put_image(game, &game->img_collectible, x, y);
	else if (tile == EXIT)
		put_image(game, &game->img_exit, x, y);
	else if (tile == PLAYER)
		put_image(game, &game->img_player, x, y);
}

void	render_map(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
				render_tile(game, x, y);
				x++;
		}
		y++;
	}
}