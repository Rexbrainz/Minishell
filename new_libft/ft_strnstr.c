/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:57:53 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 14:28:42 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len-- >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
/*
int main(void)
{
	char *s = "Success Daniel";
	char *needle = "Daniel";
	char *hay = ft_strnstr(s, needle, 14);
	char *hay1 = strnstr(s, needle, 14);
	printf("%s\n%s\n", hay, hay1);
	return (0);
}
*/
