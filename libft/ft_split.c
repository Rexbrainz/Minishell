/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 06:18:19 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 16:06:37 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		number_of_words(const char *s, char c);
static char		*my_malloc(char **p, size_t len, size_t	*num_words);
static size_t	len(const char *s, char c);

/*
int	main(void)
{
	char *s = " To    C    or    not to C, that is the question.    ";
	char c = ' ';
	char **p = ft_split(s, c);
	if (p == NULL) // Check if allocation succeeded
	{
		fprintf(stderr, "Memory allocation failed\n");
		return (1);
	}
	
	// Print and free allocated strings
	for (char **temp = p; *temp != NULL; temp++)
	{
	    printf("%s\n", *temp);
	    free(*temp); // Freeing each allocated string
	}
	free(p); // Freeing the array of pointers
	return (0);
}
*/

char	**ft_split(char const *s, char c)
{
	size_t		string_len;
	size_t		num_words;
	char		**p_strings;
	size_t		index;

	num_words = number_of_words(s, c);
	p_strings = (char **) malloc((sizeof(char *) * (num_words + 1)));
	if (!p_strings)
		return (NULL);
	index = 0;
	while (*s && index < num_words)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		string_len = len(s, c);
		if (! my_malloc(p_strings, string_len + 1, &index))
			return (NULL);
		ft_strlcpy(p_strings[index++], s, string_len + 1);
		s += string_len;
	}
	p_strings[index] = NULL;
	return (p_strings);
}

static size_t	len(const char *s, char c)
{
	const char	*p;
	size_t		len;

	p = ft_strchr(s, c);
	if (!p)
		len = ft_strlen(s);
	else
		len = p - s;
	return (len);
}

static int	number_of_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		s++;
	}
	return (count);
}

static char	*my_malloc(char **p, size_t len, size_t	*index)
{
	p[*index] = (char *) malloc(len);
	if (!p[*index])
	{
		while (*index)
			free(p[--(*index)]);
		free(p);
		return (NULL);
	}
	return (p[*index]);
}
