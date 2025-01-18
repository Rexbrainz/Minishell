/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:28:58 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/29 09:12:00 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_c(unsigned char c, va_list ap);

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	int				count;
	int				check;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format != '%')
		{
			if (write(1, format++, 1) == -1)
				return (-1);
			count++;
			continue ;
		}
		if (*format == '%')
		{
			check = is_c(*++format, ap);
			if (check == -1)
				return (-1);
			count += check;
		}
		format++;
	}
	return (va_end(ap), count);
}

static int	is_c(unsigned char c, va_list ap)
{
	int	result;

	result = 0;
	if (c == 'c')
		result = print_char(va_arg(ap, int));
	else if (c == 'd' || c == 'i')
		result = print_int(va_arg(ap, int));
	else if (c == 's')
		result = print_string(va_arg(ap, char *));
	else if (c == 'u')
		result = print_unsigned_int(va_arg(ap, unsigned int));
	else if (c == 'p')
		result = print_pointer(va_arg(ap, void *));
	else if (c == 'x')
		result = print_hexl(va_arg(ap, unsigned int));
	else if (c == 'X')
		result = print_hexu(va_arg(ap, unsigned int));
	else if (c == '%')
	{
		if (write(1, "%", 1) == -1)
			return (-1);
		result = 1;
	}
	return (result);
}
