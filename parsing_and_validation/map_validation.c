/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:08:51 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 12:18:26 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int check_rectangular(t_map *map)
{
	int y;
	int width;

	y = 0;
	while (y < map->height)
	{
		width = ft_strlen(map->grid[y]);
		if (width != map->width)
			return (0);
		y++;
	}
	return (1);
}

int	check_walls(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->width)
	{
		if (map->grid[0][x] != WALL || map->grid[map->height - 1][x] != WALL)
			return (0);
		x++;
	}
	y = 0;
	while (y < map->height)
	{
		if (map->grid[y][0] != WALL || map->grid[y][map->width - 1] != WALL)
			return (0);
		y++;
	}
	return (1);
}

int	check_valid_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] != WALL && map->grid[y][x] != EMPTY && 
				map->grid[y][x] != PLAYER && map->grid[y][x] != COLLECTIBLE && 
				map->grid[y][x] != EXIT)
			{
				ft_printf("Invalid char at [%d][%d]: '%c' (ASCII: %d)\n", 
					y, x, map->grid[y][x], map->grid[y][x]);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_element_count(t_map *map)
{
	if (map->players != 1)
		return (0);
	if (map->exits != 1)
		return (0);
	if (map->collectibles < 1)
		return (0);
	return (1);
}

int	validate_map(t_map *map)
{
	if (!check_rectangular(map))
	{
		free_map(map->grid);
		error_exit("Error\nMap is not rectangular\n");
	}
	if (!check_valid_chars(map))
	{
		free_map(map->grid);
		error_exit("Error\nMap contains invalid characters\n");
	}
	if (!check_walls(map))
	{
		free_map(map->grid);
		error_exit("Error\nMap is not surrounded by walls\n");
	}
	if (!check_element_count(map))
	{
		free_map(map->grid);
		error_exit("Error\nInvalid number of players/exits/collectibles\n");
	}
	if (!check_valid_path(map))
	{
		free_map(map->grid);
		error_exit("Error\nNo valid path to all collectibles and exit\n");
	}
	return (1);
}