/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:06:54 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/08 16:10:08 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
		return (1);
	return (0);
}
/*
int main(void)
{
	printf("%d\n", ft_isalpha('Z'));
	printf("%d\n", ft_isalpha('*'));
	printf("%d\n", isalpha('Z'));
	printf("%d\n", isalpha('*'));
	return (0);
}
*/
