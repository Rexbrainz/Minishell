/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:39:03 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/09 16:02:32 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	index;

	srclen = ft_strlen(src);
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
	return (srclen);
}
/*
int main(void)
{
	char s[] = "Hello, Success";
	char d[20];
	char d1[20];
	size_t n, n1;
	n = ft_strlcpy(d, s, sizeof(d));
	n1 = strlcpy(d1, s, sizeof(d1));
	printf("%zu\n%zu\n", n, n1);
	printf("%s\n%s\n", d, d1);
	return (0);
}
*/
