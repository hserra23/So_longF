/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:06:48 by hserra            #+#    #+#             */
/*   Updated: 2025/10/15 16:05:56 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	char tile;
	
	if (new_x < 0 || new_x >= game->map.width || new_y < 0 || new_y >= game->map.height)
		return(0);
	tile = game->map.grid[new_y][new_x];
	if (tile == WALL)
		return (0);
	if (tile == EXIT && game->collected < game->map.collectibles)
		return(0);
	return(1);
}

void move_player(t_game *game, int new_x, int new_y, int old_x)
{
	char tile;
	int old_y;

	if(!can_move(game, new_x, new_y))
		return;
	old_x = game->map.player_pos.x;
	old_y = game->map.player_pos.y;
	tile = game->map.grid[new_y][new_x];
	if (tile == COLLECTIBLE)
	{
		game->collected++;
		game->map.grid[new_y][new_x] = EMPTY;
	}
	else if (tile == EXIT && game->collected == game->map.collectibles)
	{
		ft_printf("You won in %d moves!\n", game->moves + 1);
		close_game(game);
	}
	game->map.grid[old_y][old_x] = EMPTY;
	game->map.grid[new_y][new_x] = PLAYER;
	game->map.player_pos.x = new_x;
	game->map.player_pos.y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
}
 
int	handle_keypress(int keycode, t_game *game)
{
	int x;
	int y;
	
	x = game->map.player_pos.x;
	y = game->map.player_pos.y;
	if (keycode == 65307 || keycode == 53)
		close_game(game);
	else if (keycode == 119 || keycode == 13 || keycode == 126)
		move_player(game, x, y - 1, 0);
	else if (keycode == 115 || keycode == 1 || keycode == 125)
		move_player(game, x, y + 1, 0);
	else if (keycode == 97 || keycode == 0 || keycode == 123)
		move_player(game, x - 1, y, 0);
	else if (keycode == 100 || keycode == 2 || keycode == 124)
		move_player(game, x + 1, y, 0);
	return (0);
	
}