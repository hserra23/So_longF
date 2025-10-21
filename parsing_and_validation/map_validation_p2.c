/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_p2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:38:38 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 16:17:04 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	validate(int (*check)(t_map *), t_map *map, char *msg)
{
	if (!check(map))
	{
		free_map(map->grid);
		error_exit(msg);
	}
}

int	validate_map(t_map *map)
{
	validate(check_rectangular, map, "Error: Map is not rectangular\n");
	validate(check_valid_chars, map,
		"Error: Map contains invalid characters\n");
	validate(check_walls, map, "Error: Map is not surrounded by walls\n");
	validate(check_element_count, map,
		"Error: Invalid number of players/exits/collectibles\n");
	validate(check_valid_path, map,
		"Error: No valid path to all collectibles and exit\n");
	return (1);
}
