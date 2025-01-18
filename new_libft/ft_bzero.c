/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:05:15 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/09 08:21:57 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = 0;
}
/*
int main(void)
{
	char s[10];
	char p[10];
	ft_bzero(s, 0);
	bzero(s, 0);
	printf("%s\n", s);
	printf("%s\n", p);
	return (0);
}
*/
