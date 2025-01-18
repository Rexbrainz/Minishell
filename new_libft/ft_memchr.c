/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:56:50 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 12:01:03 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *)s;
	ch = (unsigned char) c;
	while (n--)
	{
		if (*p == ch)
			return ((void *)p);
		p++;
	}
	return (NULL);
}
/*
int main(void)
{
	char *s = "REx";
	char *p = ft_memchr(s, 'R', 3);
	char *p1 = memchr(s, 'R', 3);
	printf("%c\n%c\n", *p, *p1);
	return (0);
}
*/
