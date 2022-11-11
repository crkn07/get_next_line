/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:14:42 by crtorres          #+#    #+#             */
/*   Updated: 2022/11/11 13:05:00 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * It takes a string and returns a pointer to a new string that contains the 
 * first line of the original string up to the newline character.
 * 
 * @param stash This is the string that contains the characters that have been 
 * read from the file descriptor.
 * 
 * @return A pointer to a string.
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
	str = malloc(sizeof(char) * (i + 2));
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
	int		j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = '\0';
	free (stash);
	return (str);
}

/**
 * It reads from the file descriptor and stores the readed data in the stash
 * 
 * @param fd file descriptor
 * @param stash the string that contains the leftover characters from the 
 * previous read.
 * 
 * @return a pointer to the first occurrence of the character c in the string s.
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
 * Read from the file descriptor and store the read data in a static variable. 
 * If the static variable contains a newline character, return the data up to 
 * the newline character. If the static variable does not contain a newline 
 * character, read from the file descriptor again and append the read data to 
 * the static variable. If the file descriptor is empty, return the data in the 
 * static variable
 * 
 * @param fd the file descriptor from which to read
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

/*int	main(void)
{
	char	*line;
	int		fd;
	get_next_line(-4);
	fd = 0;
	if (fd == -1)
		return (-1);
	fd = open("fil", O_RDONLY);
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	fd = close(fd);
	return (0);
}*/