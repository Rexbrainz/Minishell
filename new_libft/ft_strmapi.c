/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:09:25 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/11 16:42:09 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	ft_toupper_with_index(unsigned int index, char c)
{
	(void)index;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	size_t			len;
	unsigned int	index;

	index = 0;
	len = ft_strlen(s);
	p = (char *) malloc(len + 1);
	if (!p)
		return (NULL);
	while (s[index])
	{
		p[index] = f(index, s[index]);
		index++;
	}
	p[index] = '\0';
	return (p);
}
/*
int main(void)
{
	char *s = "We are trying, really";
	char *p = ft_strmapi(s, ft_toupper_with_index);
	if (p)
	{
		printf("Original: %s\n", s);
		printf("Modified: %s\n", p);
		free(p);
	}
	else
		printf("Cannot allocate memory\n");
	return (0);
}
*/
