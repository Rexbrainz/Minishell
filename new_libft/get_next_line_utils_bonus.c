/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:42:28 by sudaniel          #+#    #+#             */
/*   Updated: 2024/12/17 14:12:13 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//	my_strlen: Returns the length of a string.
size_t	my_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

// find_first_c:	Searches for and returns the first occurence
// of a character or NULL when it is not found.
char	*find_first_c(char *s, unsigned char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if ((unsigned char)*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

// fetch_line: copies destsize - 1 bytes from source dest and 
// returns the number of characters copied.
// it returns 0 if the string is empty or NULL.

char	*fetch_line(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	index;

	if (!dst || !src)
		return (NULL);
	srclen = my_strlen(src);
	index = 0;
	if (dstsize > 0)
	{
		while (index < dstsize - 1 && src[index])
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (dst);
}

//	duplicate: Allocates size of s + 1 memory space and copies 
//	all of s in to the allocated memory. 

char	*duplicate(const char *s1)
{
	char	*p;
	size_t	size;

	if (!s1)
		return (NULL);
	size = my_strlen(s1) + 1;
	p = (char *) malloc(size);
	if (!p)
		return (NULL);
	p = fetch_line(p, s1, size);
	return (p);
}

//	Join:	Joins two strings together and returns them, returns NULL
//	when any of them is empty.
char	*join(char *s, char *s1)
{
	char	*temp;
	size_t	size;
	size_t	size1;
	size_t	i;

	if (!s && !s1)
		return (NULL);
	size = my_strlen(s);
	size1 = my_strlen(s1);
	temp = (char *) malloc(size + size1 + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	}
	while (*s1)
		temp[i++] = *s1++;
	temp[i] = '\0';
	return (temp);
}
