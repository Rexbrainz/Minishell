/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 08:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 08:31:01 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <ctype.h>

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
/*
int main(void)
{
	char *s = "\tH\va\fl\rl\no ";
	while (*s)
	{
		if (ft_isspace(*s))
		{
			ft_printf("ft: I am a space, %d\n", ft_isspace(*s));
			ft_printf("is: I am a space, %d\n", isspace(*s));
		}
		else
		{
			ft_printf("ft: I am not a space, %d\n", ft_isspace(*s));
			ft_printf("is: I am not a space, %d\n", isspace(*s));
		}
		s++;
	}
	return (0);
}
*/
