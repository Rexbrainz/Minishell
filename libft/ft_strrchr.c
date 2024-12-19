/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:41:50 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/09 11:10:06 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = s;
	c = (unsigned char)c;
	while (*s)
	{
		if (*s == c)
			p = s;
		s++;
	}
	if (*p == c)
		return ((char *)p);
	else if (c == '\0')
		return ((char *)s);
	return (NULL);
}
/*
int main(void)
{
	char *s = "tripouille";
	printf("%s\n", ft_strrchr(s,'t' + 256));
	printf("%s\n", strrchr(s, 't' + 256));
	return (0);
}
*/
