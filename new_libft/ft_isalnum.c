/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:40:24 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/08 16:06:16 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	return (0);
}
/*
int	main(void)
{
	printf("%d\t%d\t%d\n", ft_isalnum('z'), ft_isalnum('4'), ft_isalnum('*'));
	printf("%d\t%d\t%d\n", isalnum('z'), isalnum('4'), isalnum('*'));
	return (0);
}
*/
