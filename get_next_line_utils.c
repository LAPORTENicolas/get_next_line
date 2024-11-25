/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:45:53 by nlaporte          #+#    #+#             */
/*   Updated: 2024/11/22 03:20:46 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include "get_next_line.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;

	if (size <= 0)
		return (ft_strlen((char *)src));
	i = 0;
	while (i < size - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen((char *)src));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*r;
	unsigned int	s_s1;
	unsigned int	s_s2;
	unsigned int	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s_s1 = ft_strlen((char *)s1);
	s_s2 = ft_strlen((char *)s2);
	i = 0;
	r = malloc(sizeof(char) * (s_s1 + s_s2 + 1));
	if (r == NULL)
		return (NULL);
	while (i < s_s1)
		r[i++] = *s1++;
	while (i < s_s1 + s_s2)
		r[i++] = *s2++;
	r[i] = '\0';
	return (r);
}

int	ft_getendline(char *s)
{
	unsigned int i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;	
	return (i);
}

unsigned int	ft_strlen(char *s)
{
	unsigned int i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
