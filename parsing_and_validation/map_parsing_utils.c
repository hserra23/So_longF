/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:38:35 by hserra            #+#    #+#             */
/*   Updated: 2025/10/15 17:37:14 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int count_lines(char *filename)
{
	int	fd;
	int	lines;
	char *line;
	
	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map file");
	line = get_next_line(fd);
	while(line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return(lines);
}

int get_map_width(char *filename)
{
    int     fd;
    char    *line;
    int     width;
    int     len;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_exit("Error\nCannot open map file");

    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        error_exit("Error\nEmpty map file");
    }
	
    // Strip trailing newline and carriage return characters
    len = ft_strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
    {
        line[len - 1] = '\0';
        len--;
    }
    width = len;  // Now this is accurate
    free(line);
    close(fd);
    return (width);
}

char	**read_map_grid(char *filename, int height, int i)
{
	char **grid;
	char *line;
	int fd;
	int len;

	grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!grid)
		error_exit("Error: Memory allocation failed");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map file");
	while (i < height)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit("Error: Failed to read map");
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
    		line[len - 1] = '\0';
    		len--;
		}
		grid[i++] = line;
	}
	grid[i] = NULL;
	close(fd);
	return (grid);
}

// static void	init_map_counts(t_map *map)
// {
// 	map->collectibles = 0;
// 	map->exits = 0;
// 	map->players = 0;
// 	map->player_pos.x = 0;
// 	map->player_pos.y = 0;
// }
