/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:18:09 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/22 15:28:41 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hexl(unsigned int x)
{
	int				count;
	unsigned int	power;
	unsigned int	ch;

	count = 0;
	power = 1;
	while (x / power > 15)
		power *= 16;
	while (power)
	{
		ch = x / power;
		if (write(1, &"0123456789abcdef"[ch], 1) == -1)
			return (-1);
		count++;
		x %= power;
		power /= 16;
	}
	return (count);
}
