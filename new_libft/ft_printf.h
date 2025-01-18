/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 06:19:23 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/28 16:11:44 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

//	ft_printf:	A version of printf that focuses on the following formats
//				c, s, p, d, i, u, x, X and %.
//				It should behave just as printf would do in handling these
//				formats.
int	ft_printf(const char *format, ...);

//	print_char:	Prints a char when format points to an address of c.
int	print_char(int c);

// print_int:	Prints an int when format points to the address of d or i.
int	print_int(int d);

// print_string: Prints a string when format points to the address of s.
int	print_string(const char *s);

// prints_unsigned_int: Prints an unsigned int when format points to the
// 						address of u. 
int	print_unsigned_int(unsigned int u);

//	prints_pointer: Prints the address of a variable when format points to 
//					the address of p.
int	print_pointer(void *p);

//	print_hexl:	Prints the address of an int in hexadecimal in lowercases
//				 when format points to x.
int	print_hexl(unsigned int x);

//	print_hexu:	Prints the address of an int in hexadecimal in uppercase
//				when format points to X.
int	print_hexu(unsigned int X);

#endif
