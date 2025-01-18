/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 06:28:29 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/09 08:22:29 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;
	unsigned char	ch;

	p = (unsigned char *)b;
	ch = c;
	while (len--)
		*p++ = ch;
	return (b);
}
/*
int	main(void)
{
	int s[10], n = 6;
	void *p = ft_memset(s, 300, n);
	void *p1 = memset(s, 300, n);
	while (n--)
	{
		printf("%d\t", *s);
		printf("%d\n", *s);
	}
	return (0);
}
*/
