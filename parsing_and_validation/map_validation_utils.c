/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:41:49 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 15:42:50 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **grid_copy, int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return ;
	if (grid_copy[y][x] == WALL || grid_copy[y][x] == 'V')
		return ;
	grid_copy[y][x] = 'V';
	flood_fill(grid_copy, x + 1, y, map);
	flood_fill(grid_copy, x - 1, y, map);
	flood_fill(grid_copy, x, y + 1, map);
	flood_fill(grid_copy, x, y - 1, map);
}

char	**copy_grid(t_map *map)
{
	char	**copy;
	int		x;
	int		y;

	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	y = -1;
	while (++y < map->height)
	{
		copy[y] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[y])
			return (free_map(copy), NULL);
		x = -1;
		while (++x < map->width)
			copy[y][x] = map->grid[y][x];
		copy[y][x] = '\0';
	}
	copy[y] = NULL;
	return (copy);
}

int	is_unreachable(t_map *map, char **grid_copy, int x, int y)
{
	if ((map->grid[y][x] == COLLECTIBLE || map->grid[y][x] == EXIT)
		&& grid_copy[y][x] != 'V')
		return (1);
	return (0);
}

int	check_valid_path(t_map *map)
{
	char	**grid_copy;
	int		x;
	int		y;

	grid_copy = copy_grid(map);
	if (!grid_copy)
		error_exit("Error\nMemory allocation failed\n");
	flood_fill(grid_copy, map->player_pos.x, map->player_pos.y, map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (is_unreachable(map, grid_copy, x, y))
			{
				free_map(grid_copy);
				return (0);
			}
			x++;
		}
		y++;
	}
	free_map(grid_copy);
	return (1);
}
