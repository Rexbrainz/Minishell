/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:32:45 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/22 11:25:29 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned_int(unsigned int u)
{
	int				count;
	unsigned int	power;
	unsigned char	digit;

	count = 0;
	power = 1;
	while (u / power > 9)
		power *= 10;
	while (power > 0)
	{
		digit = u / power + '0';
		if (write(1, &digit, 1) == -1)
			return (-1);
		count++;
		u %= power;
		power /= 10;
	}
	return (count);
}
