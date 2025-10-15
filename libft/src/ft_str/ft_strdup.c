/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hserra <hserra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:03:13 by hserra            #+#    #+#             */
/*   Updated: 2025/10/15 17:18:41 by hserra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char    *ft_strdup(const char *s)
{
    int     len = ft_strlen(s);
    char    *copy = malloc(len + 1);
    if (!copy)
        return (NULL);
    for (int i = 0; i < len; i++)
        copy[i] = s[i];
    copy[len] = '\0';
    return (copy);
}
