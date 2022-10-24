/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:37:08 by crtorres          #+#    #+#             */
/*   Updated: 2022/10/24 16:25:08 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	a;

	a = 0;
	if (!str)
		return (0);
	while (str[a] != '\0')
	{
		a++;
	}
	return (a);
}

/**
 * It takes two strings and joins them together.
 * 
 * @param s1 The first string to be joined.
 * @param s2 The string to be appended to the end of s1.
 * 
 * @return A pointer to a new string that is the result of the 
 * concatenation of s1 and s2.
 */
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_string;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new_string == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
		{
			new_string[i] = s1[i];
		}
	while (s2[j] != '\0')
	{
		new_string[i + j] = s2[j];
		j++;
	}
	new_string[i + j] = '\0';
	free(s1);
	return (new_string);
}

/**
 * The function ft_strchr() locates the first occurrence of c (converted to 
 * a char) in the string pointed to by s
 * 
 * @param str This is the string to be searched.
 * @param c The character to search for.
 * 
 * @return A pointer to the first occurrence of the character c in the 
 * string str.
 */
char	*ft_strchr(char *str, int c)
{
	int	i;
	
	i = 0;
	if (!str)
		return (NULL);
	if (c == '\0')
		return ((char *)&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
			if (str[1] == (char) c)
				return ((char *)&str[i]);
			i++;
	}	
	return (0);
}
