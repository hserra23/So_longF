/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:10:49 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 16:16:38 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_elements(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == COLLECTIBLE)
				map->collectibles++;
			else if (map->grid[y][x] == EXIT)
				map->exits++;
			else if (map->grid[y][x] == PLAYER)
			{
				map->players++;
				map->player_pos.x = x;
				map->player_pos.y = y;
			}
			x++;
		}
		y++;
	}
}

t_map	parse_map(char *filename)
{
	t_map	map;
	int		i;

	i = 0;
	if (!filename)
		error_exit("Error: No map file provided\n");
	if (ft_strlen(filename) < 4 || ft_strncmp(filename + ft_strlen(filename)
			- 4, ".ber", 4) != 0)
		error_exit("Error: Map file must have .ber extension\n");
	map.height = count_lines(filename);
	map.width = get_map_width(filename);
	if (map.height < 3 || map.width < 3)
		error_exit("Error: Map too small (minimum 3x3)\n");
	map.grid = read_map_grid(filename, map.height, i);
	if (!map.grid)
		error_exit("Error: Failed to allocate map grid\n");
	map.collectibles = 0;
	map.exits = 0;
	map.players = 0;
	map.player_pos.x = 0;
	map.player_pos.y = 0;
	count_map_elements(&map);
	return (map);
}

void	free_map(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
