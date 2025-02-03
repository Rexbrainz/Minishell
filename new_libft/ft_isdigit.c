/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:29:46 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/08 16:02:05 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
int main(void)
{
	printf("%d\t%d\t%d\t\n", ft_isdigit('0'), ft_isdigit('z'), ft_isdigit('2'));
	printf("%d\t%d\t%d\t\n", isdigit('0'), isdigit('z'), isdigit('2'));
	return (0);
}
*/
