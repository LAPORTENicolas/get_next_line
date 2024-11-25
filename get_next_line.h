/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 19:45:23 by nlaporte          #+#    #+#             */
/*   Updated: 2024/11/22 03:20:56 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

typedef struct s_file
{
	char	buf[BUFFER_SIZE + 1];
	char	*line;
	int		init;
	int		fd;
	int		status;
	int		index;
}	t_file;

char				*get_next_line(int fd);
char				*ft_strjoin(const char *s1, const char *s2);

unsigned int		ft_strlcpy(char *dest, const char *src, unsigned int size);
unsigned int		ft_strlcat(char *dest, const char *src, unsigned int size);
int		ft_getendline(char *s);
unsigned int		ft_strlen(char *s);
#endif // !GET_NEXT_LINE_H
