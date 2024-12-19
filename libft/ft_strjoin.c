/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:43:14 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 17:01:40 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*p;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = (char *) malloc(size);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s1, ft_strlen(s1) + 1);
	ft_strlcat(p, s2, size);
	return (p);
}
/*
int main(void)
{
	char *s1 = "Success";
	char *s2 = "Daniel";
	char *p = ft_strjoin(s1, s2);
	printf("%s\n", p);
	return (0);
}
*/
