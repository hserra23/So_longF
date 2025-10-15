/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:00:43 by hserra            #+#    #+#             */
/*   Updated: 2025/10/10 17:06:46 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	error_exit(char *message)
{
	write(2, message, ft_strlen(message));
	exit(1);
}
int ft_strlen(char *str)
{
	int i;
	
	if(!str)
		return(0);
	i = 0;
	while (str[i])
		i++;
	return(i);
}
int ft_strncmp(char *s1, char *s2, int n)
{
	int i;
	
	if (!s1 || !s2)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}