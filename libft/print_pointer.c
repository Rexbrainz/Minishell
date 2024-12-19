/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:54:13 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/29 07:40:59 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *p)
{
	int				count;
	char			*hex_array;
	unsigned long	i;
	unsigned long	power;

	count = 0;
	hex_array = "0123456789abcdef";
	if (write(1, "0x", 2) == -1)
		return (-1);
	count += 2;
	power = 1;
	i = (unsigned long) p;
	while (i / power > 15)
		power *= 16;
	while (power)
	{
		if (write(1, &hex_array[i / power], 1) == -1)
			return (-1);
		count++;
		i %= power;
		power /= 16;
	}
	return (count);
}
