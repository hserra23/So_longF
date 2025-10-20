/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:08:31 by hserra            #+#    #+#             */
/*   Updated: 2025/10/20 15:55:59 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_get_next_line.h"
#include "../../inc/libft.h"

int	ft_linelen(char *str)
{
	int	count;

	count = 0;
	while (str && str[count] && str[count] != '\n')
		count++;
	if (str && str[count] == '\n')
		count++;
	return (count);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		count;
	int		count2;
	char	*joined;

	count = 0;
	joined = (char *)malloc(ft_linelen(s1) + ft_linelen(s2) + 1);
	if (!joined)
		return (free(s1), NULL);
	while (s1 && s1[count])
	{
		joined[count] = s1[count];
		count++;
	}
	count2 = 0;
	while (s2[count2] != '\n' && s2[count2])
	{
		joined[count + count2] = s2[count2];
		count2++;
	}
	if (s2[count2] == '\n')
		joined[count + count2++] = '\n';
	joined[count + count2] = '\0';
	if (s1)
		free(s1);
	return (joined);
}

void	buffer_clean(char *str)
{
	int	count;
	int	count2;

	count = 0;
	count2 = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\n')
	{
		count++;
		while (str[count])
			str[count2++] = str[count++];
	}
	while (count2 < BUFFER_SIZE)
		str[count2++] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			count;

	count = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		while (count <= BUFFER_SIZE)
			buffer[count++] = '\0';
		return (NULL);
	}
	str = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
		buffer_clean(buffer);
		if (str[ft_linelen(str) - 1] == '\n')
			return (str);
	}
	return (str);
}
