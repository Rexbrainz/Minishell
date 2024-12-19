/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:29:52 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/11 16:05:06 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_n_len(int n, unsigned int *temp, int *power);

char	*ft_itoa(int n)
{
	unsigned int	index;
	unsigned int	num_len;
	unsigned int	temp;
	int				power;
	char			*p;

	index = 0;
	power = 1;
	num_len = get_n_len(n, &temp, &power);
	p = (char *) malloc(num_len + 1);
	if (!p)
		return (NULL);
	if (n < 0)
	{
		p[index] = '-';
		index++;
	}
	while (power > 0)
	{
		p[index++] = temp / power + '0';
		temp %= power;
		power /= 10;
	}
	p[index] = '\0';
	return (p);
}

static int	get_n_len(int n, unsigned int *temp, int	*power)
{
	int	num_len;

	num_len = 0;
	if (n < 0)
	{
		*temp = -n;
		num_len++;
	}
	else if (n == 0)
	{
		*temp = 0;
		return (1);
	}
	else
		*temp = n;
	while (*temp / *power >= 10)
	{
		*power *= 10;
		num_len++;
	}
	return (num_len + 1);
}
/*
int main(void)
{
	int num = INT_MIN;
	char *s = ft_itoa(num);
	printf("%s\n", s);
	return (0);
}
*/
