/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:09:35 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 12:21:12 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	index;
	size_t	size;
	size_t	substr_len;

	index = 0;
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	substr_len = size - start;
	if (substr_len < len)
		len = substr_len;
	p = (char *) malloc(len + 1);
	if (!p)
		return (NULL);
	while (len-- && start < size)
		p[index++] = s[start++];
	p[index] = '\0';
	return (p);
}
/*
int main(void)
{
	char *s = "Daniel";
	unsigned int start = 2;
	size_t len = 4;
	char *p = ft_substr(s, start, len);
	printf("%s\n", p);
	return (0);
}
*/
