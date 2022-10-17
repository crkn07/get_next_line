/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:36:37 by crtorres          #+#    #+#             */
/*   Updated: 2022/10/17 12:06:31 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
char	*get_next_line(int fd)
{
	char		*readstr;
	static char	*backup[OPEN_MAX];
	char		*str;
	int			readsize;
	int			i;

	i = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= OPEN_MAX)
		return (0);
}
*/
/**
 * It checks if there's a newline in the buffer, if there is, it copies the line
 * into the line pointer, and the rest of the buffer into a static variable, and
 * returns 1. If there's no newline, it copies the buffer into the line pointer,
 * and returns 0
 * 
 * @param pos This is the position of the buffer.
 * @param line the address of a pointer to a character that will be used to save
 * the line read from the file descriptor.
 * 
 * @return the number of bytes read.
 */
int	check_buffer(char *pos, char **line)
{
	char		*aux;
	char		*otro;
	static char	aux2[BUFFER_SIZE + 1];

	aux = ft_strchr(pos, '\n');
	otro = *line;
	if (aux)
	{
		*aux = '\0';
		*line = ft_strjoin(otro, pos);
		free(otro);
		ft_memcpy(aux2, aux + 1, ft_strlen(aux + 1));
		ft_bzero(pos, BUFFER_SIZE + 1);
		ft_memcpy(pos, aux2, ft_strlen(aux2));
		ft_bzero(aux2, BUFFER_SIZE + 1);
		otro = *line;
		*line = ft_strjoin(otro, "\n");
		free(otro);
		return (1);
	}
	*line = ft_strjoin(otro, pos);
	free(otro);
	ft_bzero(pos, BUFFER_SIZE + 1);
	return (0);
}

/**
 * It reads a file descriptor, line by line, and returns a pointer to the 
 * line read
 * 
 * @param fd file descriptor
 * 
 * @return A line of text from a file.
 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	pos[BUFFER_SIZE + 1];
	int			rd;

	line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0 || !line)
		return (freeline(line));
	ft_bzero(line, BUFFER_SIZE + 1);
	if (check_buffer(pos, &line))
		return (line);
	rd = read(fd, pos, BUFFER_SIZE);
	while (rd && rd != -1)
	{
		if (check_buffer(pos, &line))
			return (line);
		rd = read(fd, pos, BUFFER_SIZE);
	}
	if (line[0] == '\0')
		return (freeline(line));
	return (line);
}
