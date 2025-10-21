/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:38:35 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 16:15:36 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(char *filename)
{
	int		fd;
	int		lines;
	char	*line;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map file\n");
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	get_map_width(char *filename)
{
	int		fd;
	char	*line;
	int		width;
	int		len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map file\n");
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		error_exit("Error: Empty map file\n");
	}
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		line[len - 1] = '\0';
		len--;
	}
	width = len;
	free(line);
	close(fd);
	return (width);
}

static void	validate_line(char *line, char **grid, int fd)
{
	int	len;

	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		line[--len] = '\0';
	if (len == 0)
	{
		free(line);
		free_map(grid);
		close(fd);
		error_exit("Error: Map contains empty lines\n");
	}
}

static int	open_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map file\n");
	return (fd);
}

char	**read_map_grid(char *filename, int height, int i)
{
	char	**grid;
	char	*line;
	int		fd;

	grid = malloc(sizeof(char *) * (height + 1));
	if (!grid)
		error_exit("Error: Memory allocation failed\n");
	fd = open_map_file(filename);
	while (i < height)
	{
		line = get_next_line(fd);
		if (!line)
		{
			free_map(grid);
			close(fd);
			error_exit("Error: Failed to read map\n");
		}
		validate_line(line, grid, fd);
		grid[i++] = line;
	}
	grid[i] = NULL;
	close(fd);
	return (grid);
}
