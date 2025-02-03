/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:29:52 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/11 17:34:14 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	digit;
	unsigned int	temp;
	int				power;

	power = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		temp = -n;
	}
	else
		temp = n;
	while (temp / power > 9)
		power *= 10;
	while (power > 0)
	{
		digit = temp / power + '0';
		write(fd, &digit, 1);
		temp %= power;
		power /= 10;
	}
}
/*
int main(void)
{
	int n  = 42;
	ft_putnbr_fd(n, 1);
	putchar('\n');
	return (0);
}
*/
