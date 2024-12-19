/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 12:18:22 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/29 07:13:42 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_signed(int d);

int	print_int(int d)
{
	int				count;
	unsigned int	temp;
	unsigned int	power;

	count = is_signed(d);
	if (count == -1)
		return (count);
	else
		temp = count;
	count = 0;
	if (d < 0)
		count++;
	power = 1;
	while (temp / power > 9)
		power *= 10;
	while (power > 0)
	{
		if (write(1, &"0123456789"[temp / power], 1) == -1)
			return (-1);
		count++;
		temp %= power;
		power /= 10;
	}
	return (count);
}

static int	is_signed(int d)
{
	unsigned int	temp;

	if (d < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		temp = -d;
	}
	else
		temp = d;
	return (temp);
}
