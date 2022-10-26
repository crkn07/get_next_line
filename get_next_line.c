/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:14:42 by crtorres          #+#    #+#             */
/*   Updated: 2022/10/26 18:33:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * It takes a string and returns a string that contains everything up to the 
 * first newline character
 * 
 * @param stash This is the string that contains the characters that 
 * have been read from the file descriptor.
 * 
 * @return a string that is the first line of the file.
 */
char	*ft_get_line(char *stash)
{
	int			i;
	static char	*str;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * It takes a string, finds the first newline character, and returns a new 
 * string containing everything after the newline
 * 
 * @param stash the string that contains the leftover characters from the 
 * previous read
 * 
 * @return A pointer to a string.
 */
char	*ft_stash(char *stash)
{
	int		i;
	int		c;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!str)
		return (NULL);
	i++;
	c = 0;
	while (stash[i])
		str[c++] = stash[i++];
	str[c] = '\0';
	free (stash);
	return (str);
}

/**
 * It reads from a file descriptor and stores the readed data in a string
 * 
 * @param fd file descriptor
 * @param stash the string that contains the leftover characters from the 
 * previous read.
 * 
 * @return A pointer to a string.
 */
char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		readed;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readed = 1;
	while (!ft_strchr(stash, '\n') && readed != 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	return (stash);
}

/**
 * Read from the file descriptor and store the read data in a static variable. If
 * the static variable contains a newline, return the data up to the newline. If
 * the static variable does not contain a newline, read from the file descriptor
 * again
 * 
 * @param fd the file descriptor
 * 
 * @return A line of text from the file descriptor.
 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_stash(stash);
	return (line);
}
