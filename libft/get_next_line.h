/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:05:55 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/28 15:56:00 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

# include <unistd.h>
# include <stdlib.h>
//	Get next line reads from a file through its file descriptor, into a buffer
//	with a given size, searches the buffer for a new line character while
//	keeping track of the first char in the buffer, returns the line read
//	including the newline character when found. if it cannot find a new line
//	character because the characters are almost finished and there is none
//	it returns the line. If there is nothing else to read or an error occured,
//	it returns NULL.
char	*get_next_line(int fd);

//	Takes a string and returns its length.
size_t	my_strlen(const char *s);

//	find_first_c:   Searches for and returns the first occurence
// 	of a character or NULL when it is not found.
char	*find_first_c(char *s, unsigned char c);

// fetch_line: copies destsize - 1 bytes from source dest and
// returns the number of characters copied.
// it returns 0 if the string is empty or NULL.
char	*fetch_line(char *dst, const char *src, size_t dstsize);

//  duplicate: Allocates size of s + 1 memory space and copies
//  all of s in to the allocated memory.
char	*duplicate(const char *s1);

//  Join:   Joins two strings together and returns them, returns NULL
//  when any of them is empty.
char	*join(char *s, char *s1);

#endif
