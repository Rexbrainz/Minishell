/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:39:08 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/08 16:54:58 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int main(void)
{
	printf("%c\t%c\n", ft_toupper('a'), ft_toupper('8'));
	printf("%c\t%c\n", toupper('a'), toupper('8'));
	return (0);
}
*/
