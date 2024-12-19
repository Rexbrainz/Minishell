/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:37:36 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 15:57:52 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			new_size;
	size_t			index;

	index = 0;
	new_size = count * size;
	p = (unsigned char *)malloc(new_size);
	if (!p)
		return (NULL);
	while (new_size--)
		p[index++] = 0;
	return ((void *)p);
}
/*
int main(void)
{
	char *s = ft_calloc(5, 1);
	int i = 0;
	while (i < 5)
		s[i++] = 'a';
	printf("%s\n", s);
	return (0);
}
*/
