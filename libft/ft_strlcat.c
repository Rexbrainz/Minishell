/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:12:09 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/10 06:43:21 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	dst += dst_len;
	dstsize -= dst_len;
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_len + src_len);
}
/*
int main(void)
{
	char s[] = " ,Success";
	char d[20] = "Hello";
	char d1[20] = "Hello";
	ft_strlcat(d, s, sizeof(d));
	strlcat(d1, s, sizeof(d1));
	printf("%s\n%s\n", d, d1);
	return (0);
}
*/
