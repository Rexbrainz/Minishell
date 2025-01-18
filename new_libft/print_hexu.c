/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:14:48 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/29 07:37:38 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hexu(unsigned int X)
{
	int				count;
	unsigned int	ch;
	unsigned int	power;

	count = 0;
	power = 1;
	while (X / power > 15)
		power *= 16;
	while (power)
	{
		ch = X / power;
		if (write(1, &"0123456789ABCDEF"[ch], 1) == -1)
			return (-1);
		count++;
		X %= power;
		power /= 16;
	}
	return (count);
}
