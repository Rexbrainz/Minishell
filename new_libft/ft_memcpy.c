/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:27:16 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/09 10:40:52 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d || s)
		while (n--)
			*d++ = *s++;
	return (dst);
}
/*
int main(void)
{
	char *src = "Hello";
	char dst[10];
	char d[10];
	ft_memcpy(d, src, 5);
	memcpy(dst, src, 5);
	printf("%s\n", dst);
	printf("%s\n", d);
	return (0);	
}
*/
