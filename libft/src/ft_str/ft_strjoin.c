/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:18 by hserra            #+#    #+#             */
/*   Updated: 2025/10/15 17:18:57 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char    *ft_strjoin(char *s1, char *s2)
{
    int     len1 = ft_strlen(s1);
    int     len2 = ft_strlen(s2);
    char    *joined = malloc(len1 + len2 + 1);
    int     i = 0, j = 0;

    if (!joined)
        return (NULL);
    while (s1 && s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    while (s2 && s2[j])
        joined[i++] = s2[j++];
    joined[i] = '\0';
    return (joined);
}