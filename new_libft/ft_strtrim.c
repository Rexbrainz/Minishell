/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:09:46 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 18:52:33 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*p;
	char		*new_string;
	size_t		new_string_len;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	p = s1 + ft_strlen(s1);
	while (p != s1 && ft_strchr(set, *(p - 1)))
		p--;
	new_string_len = p - s1;
	new_string = (char *) malloc(new_string_len + 1);
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, s1, new_string_len + 1);
	return (new_string);
}
/*
int main(void)
{
	char *s = "iiiSuccessiii";
	char *i = "iii";
	char *p = ft_strtrim(s, i);
	printf("%s\n", p);
	return (0);
}
*/
