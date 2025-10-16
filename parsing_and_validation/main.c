/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:18:02 by hserra            #+#    #+#             */
/*   Updated: 2025/10/16 13:59:43 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    t_game game;
    
    if (argc != 2)
    {
        ft_printf("Usage: %s <map_file.ber>\n", argv[0]);
        return (1);
    }
    
    ft_printf("Step 1: Starting...\n");
    fflush(stdout);
    
    init_game(&game, argv[1]);

	ft_printf("=== MAP INFO ===\n");
	ft_printf("Players: %d (expected: 1)\n", game.map.players);
	ft_printf("Exits: %d (expected: 1)\n", game.map.exits);
	ft_printf("Collectibles: %d (expected: >= 1)\n", game.map.collectibles);
	ft_printf("================\n");
    
    ft_printf("Step 2: After init_game\n");
    fflush(stdout);
    
    render_map(&game);
    
    ft_printf("Step 3: After render_map\n");
    fflush(stdout);
    
    mlx_hook(game.win, 2, 1L << 0, handle_keypress, &game);
    mlx_hook(game.win, 17, 0, close_game, &game);
    
    ft_printf("Step 4: Before loop\n");
    fflush(stdout);
    
    mlx_loop(game.mlx);
    return (0);
}
