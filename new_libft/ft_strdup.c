/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:06:39 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 15:45:20 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	size;

	size = ft_strlen(s1) + 1;
	p = (char *) malloc(size);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, size);
	return (p);
}
/*
int main(void)
{
	char *s = "Hello";
	char *p = ft_strdup(s);
	printf("%s\n", p);
	return (0);
}
*/
