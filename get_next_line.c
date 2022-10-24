/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.cj                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10free (stash);
return (str);/03 18:36:37 by crtorres          #+#    #+#             */
/*   Updated
: 2022/10/24 14:43:55 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * It takes a string and returns a string that contains everything up to the first
 * newline character
 * 
 * @param stash This is the string that contains the characters that have been read
 * from the file descriptor.
 * 
 * @return a string that is the first line of the file.
 */
char	*ft_get_line(char *stash)
{
	int		i;
	char	*str;
	
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
 * It takes a string and returns a copy of that string with the first character
 * removed
 * 
 * @param stash the string to be stashed
 * 
 * @return A pointer to a string.
 */
char	*ft_stash(char *stash)
{
	int		i;
	int		j;
	char	*str;
	i = 0;
	while (stash[i] && stash[i] != 0)
		i++;
	if (!stash)
	{
		free (stash);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
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
 * It reads from a file descriptor and stores the readed data in a string
 * 
 * @param fd file descriptor
 * @param stash the string that contains the leftover characters from the previous
 * read.
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
		if (readed == -1)
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

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_get_line(stash);
	stash = ft_stash(stash);
	return (line);
}
