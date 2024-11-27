/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 05:28:53 by nlaporte          #+#    #+#             */
/*   Updated: 2024/11/22 06:08:38 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void clear_buffer(t_file *file)
{
	int i;

	i = 0;
	while (i <= BUFFER_SIZE)
		file->buf[i++] = '\0';
}

void clear_file(t_file *file)
{
	clear_buffer(file);
	file->fd = 0;
	file->init = 0;
	file->line = NULL;
	file->status = 0;
	file->index = 0;
}

void	init_file(t_file *file, int fd)
{
	file->fd = fd;
	file->init = 1;
	file->line = NULL;
	clear_buffer(file);
	file->status = read(fd, file->buf, BUFFER_SIZE);
	printf("file buf = %s", file->buf);
}

void debug(t_file *file);

void	realloc_char(t_file *file, int linebreak)
{
	int line_len;
	int buf_len;
	int i;
	int j;
	char *new;

	line_len = ft_strlen(file->line);
	buf_len = ft_getendline(&file->buf[file->index]);/*
	debug(file);
	printf("\nindex start = %i\n", file->index);
	printf("\nchar start = %c\n", file->buf[file->index]);*/
	if (linebreak)
		new = malloc(sizeof(char) * (line_len + buf_len + 2));
	else
		new = malloc(sizeof(char) * (line_len + buf_len + 1));
	if (new == NULL)
		return ;
	i = 0;
	j = file->index;
	while (i < line_len && file->line != NULL)
	{
		new[i] = file->line[i];
		i++;
	}
	while (j - file->index < buf_len)
		new[i++] = file->buf[j++];
	if (linebreak)
		new[i++] = '\n';
	new[i] = '\0';
	file->index = j;
	if (file->line != NULL)
		free(file->line);
	file->line = new;
}

void	debug(t_file *f)
{
	printf(" ---- | debug | ---- \n");
	printf("fd: %i\n", f->fd);
	printf("status: %i\n", f->status);
	printf("index: %i\n", f->index);
	printf("buf: %s\n", f->buf);
	if (f->line != NULL)
		printf("line: %s\n", f->line);
}

char	*next_line(t_file *file)
{
	char *tmp;
	// Vérifie s'il reste du text sinon return NULL
	if (file->index == BUFFER_SIZE)
	{
		// Je remplis buffer avec la suite du fichier
		clear_buffer(file);
		file->status = read(file->fd, file->buf, BUFFER_SIZE);
		// Je retablie l'index a 0
		file->index = 0;
	}
	// Vérifie les erreurs de lecture
	if (file->status == -1)
	{
		if (file->line)
			free(file->line);
		clear_file(file);
		return (NULL);
	}
	// Tant que pas a la fin de la ligne
	// Copier dans line le contenue du buffer
	//debug(file);
	while (file->status > 0)
	{
		// J'apelle la fonction que copie de l'index ou je suis
		// jusqu'a l'index de fin de ligne en concatenant avec line
		realloc_char(file, 0);
		if (file->index >= BUFFER_SIZE)
		{
			file->index = 0;
			clear_buffer(file);
			file->status = read(file->fd, file->buf, BUFFER_SIZE);
			if (file->status == -1)
			{
				if (file->line)
					free(file->line);
				clear_file(file);
				return (NULL);
			}
		} else if (file->buf[file->index] == '\n') {
			realloc_char(file, 1);
			file->index++;
			break;
		} else if (file->buf[BUFFER_SIZE - 1] == '\0')
		{
			(void)tmp;
			return (NULL);
		}
	}
	/*
		printf("index = %i\n", file->index);
		printf("status = %i\n", file->status);
		printf("buf[status] = %i\n\n", file->buf[file->status]);
		*/
		// Actualise le status		realloc_char(file, 0);
	/*if (file->buf[file->index - 1] == 0)
	{
		tmp = file->line;
		clear_file(file);
		return tmp;
	}*/
	//printf("fin buf = %s\n", file->buf);
	return (file->line);
}

char	*get_next_line(int fd)
{
	static t_file file[1025];
	char *tmp;

	if (file[fd].init == 0)
		init_file(&file[fd], fd);
	if (file[fd].line != NULL)
		file[fd].line = NULL;
	//printf("file = %s\n", file[fd].buf);
	tmp = next_line(&file[fd]);
	if (tmp == NULL)
	{
		clear_file(&file[fd]);
		return (NULL);
	}
	return (tmp);
}
