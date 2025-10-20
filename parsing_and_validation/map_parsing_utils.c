/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:38:35 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 12:26:22 by hserra           ###   ########.fr       */
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
		error_exit("Error: Cannot open map file\n");
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
        error_exit("Error\nCannot open map file\n");
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        error_exit("Error\nEmpty map file\n");
    }
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

char **read_map_grid(char *filename, int height, int i)
{
	char **grid;
	char *line;
	int fd;
	int len;

	grid = (char **)malloc(sizeof(char *) * (height + 1));
	if (!grid)
		error_exit("Error\nMemory allocation failed");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(grid);
		error_exit("Error\nCannot open map file");
	}
	while (i < height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_map(grid);
			close(fd);
			error_exit("Error\nFailed to read map");
		}
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
			line[len - 1] = '\0';
			len--;
		}
		if (len == 0)
		{
			free(line);
			free_map(grid);
			close(fd);
			error_exit("Error\nMap contains empty lines");
		}
		grid[i++] = line;
	}
	grid[i] = NULL;
	close(fd);
	return (grid);
}

