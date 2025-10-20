/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:37:11 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 14:56:08 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_images(t_game *game)
{
	if (game->img_wall.img)
		mlx_destroy_image(game->mlx, game->img_wall.img);
	if (game->img_floor.img)
		mlx_destroy_image(game->mlx, game->img_floor.img);
	if (game->img_player.img)
		mlx_destroy_image(game->mlx, game->img_player.img);
	if (game->img_collectible.img)
		mlx_destroy_image(game->mlx, game->img_collectible.img);
	if (game->img_exit.img)
		mlx_destroy_image(game->mlx, game->img_exit.img);
}

int	close_game(t_game *game)
{
	destroy_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map.grid)
		free_map(game->map.grid);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}
