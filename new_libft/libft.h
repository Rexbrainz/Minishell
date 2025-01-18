/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 12:58:33 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 08:12:34 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "get_next_line_bonus.h"
# include "ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//	 ft_isalpha:  Tests if a character is an aphabet or not, returns
//               zero if false and non-zero when true.
int		ft_isalpha(int c);

//	ft_isdigit: Tests if a character is a number, it returns non-zero
//				when truen and 0 when false.
int		ft_isdigit(int c);

//	ft_isalnum: Tests if a character is alphanumeric, returns non-zero
//				when true and zero when false.
int		ft_isalnum(int c);

//	ft_isascii: Tests if a character is an ascii character, returns 
//				non-zero when true and zero when false.
int		ft_isascii(int c);

//	ft_isspace:	Tests if a character is considered a space or not,
//				returns 0, if false and 1 when true.
int		ft_isspace(int c);

//	ft_isprint: Tests if a character is printable, returns non-zero
//				when true and zero when false.
int		ft_isprint(int c);

//	ft_toupper: Converts lowercase letters to uppercase and returns 
//				it, otherwise returns the character unchanged.
int		ft_toupper(int c);

//	ft_tolower: Converts uppercase letters to lowercase and returns i,t
//				otherwise returns the character unchanged.
int		ft_tolower(int c);

//	ft_strchr: Searches for the first occurence of c in the string s,
//			   returns it when found, otherwise returns NULL.
char	*ft_strchr(const char *s, int c);

//	ft_strrchr: Searches for the last occurence of c in the string s,
//				returns it when found, otherwise returns NULL.
char	*ft_strrchr(const char *s, int c);

//	ft_strlen:	Calculates and returns the number of characters in s.
size_t	ft_strlen(const char *s);

//	ft_memset:	Takes a void pointer, fills it with len bytes of the 
//				char c and returns the pointer.
void	*ft_memset(void *b, int c, size_t len);

//	ft_bzero:	Fills the string s, with n number of zeros, returns
//				nothing.
void	ft_bzero(void *s, size_t n);

//	ft_memcpy:	Copies n bytes from src to dst, does not care about 
//				memory overlapping. returns dst.
void	*ft_memcpy(void *dst, const void *src, size_t n);

//	ft_memchr:	Searches the first occurence of c in s, returns a 
//				pointer to the byte located or NULL when not.
void	*ft_memchr(const void *s, int c, size_t n);

//	ft_memcmp:	Compares n bytes of s1 and s2 and returns an int based
//				on if a character in s1 is greater, equal or less than s2.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

//	ft_memove:	Copies len bytes form src to dst, when they overlap, care
//				must be taken to avoid data loss, it returns dst.
void	*ft_memmove(void *dst, const void *src, size_t len);

//	ft_strlcpy:	Copies destsize - 1 characters from src to dst, if dest
//				is greater than 0, then it is null terminated. It 
//				returns the size of src.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//	ft_strlcat:	Appends dstsize - strlen(dst) - 1 characters form src to dst,
//				Null terminates dst unless dstsize is 0 or dst capacity is 
//				greater than dstsize. Returns sum of length of src and dst.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

//	ft_strncmp:	Compares n characters between s1 and s2, it returns an int
//				value based on if s1 is greater than, equal or less than s2.
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//	ft_strnstr:	Searches len times in haystack for needle, returns haystack
//				if needle is empty, returns the pointer to the first instance of
//				needle in haystack when needle is seen and NULL when not found.
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

//	ft_atoi:	Converts str to its int equivalent.
int		ft_atoi(const char *str);

//	ft_calloc:	Allocates memory for count * size and fills them with zero and 
//				returns a pointer to the allocated memory.
void	*ft_calloc(size_t count, size_t size);

//	ft_strdup:	Allocates enough memory for s1, duplicates s1 into that memory 
//				returns the pointer to that memory.
char	*ft_strdup(const char *s1);

//	ft_substr:	Creates a substring of length len from s at index start,
//				returns the substring or NULL when malloc fails.
char	*ft_substr(char const *s, unsigned int start, size_t len);

//	ft_strjoin:	Joins two strings together and returns a pointer to the
//				allocated memory for the new string.
char	*ft_strjoin(char const *s1, char const *s2);

//	ft_strtrim:	Searches for the occurence of set in the beginning and end of
//				s1, allocates memory for the trimmed string and returns it.
char	*ft_strtrim(char const *s1, char const *set);

//	ft_split:	Splits a string s when it finds a delimeter c, allocates memory
//				for each string created during split and returns a pointer to
//				the array of pointers to these splitted strings.
char	**ft_split(char const *s, char c);

//	ft_itoa:	Converts the integer n to string and returns the string, returns
//				NULL if malloc failed.
char	*ft_itoa(int n);

//	ft_strmapi:	Iterates through s and applies the function pointer f to the 
//				characters. returns the string created resulting from f, or
//				NULL when malloc fails.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

//	ft_striteri: Applies f on the characters in s, using their index, as first
//				 argument. Both function return nothing.
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//	ft_putchar_fd: Writes the char c to the file using the file's descriptor.
//				   Returns nothing.
void	ft_putchar_fd(char c, int fd);

//	ft_putstr_fd: Writes the string s to the file descriptor. Returns nothing.
void	ft_putstr_fd(char *s, int fd);

//	ft_putendl_fd: Writes the string s and a new_line char to the file
//				descriptor. It returns nothing.
void	ft_putendl_fd(char *s, int fd);

//	ft_putnbr_fd: Outputs the integer n to the given file descriptor.
//				  Returns nothing.
void	ft_putnbr_fd(int n, int fd);

//	ft_lstnew:	Creates a new linked list, makes and adds a node to the list,
//				initializes its members and returns the new node/list.
t_list	*ft_lstnew(void *content);

//	ft_lstadd_front:	Takes two parameters, a list and a new node to add to
//						the beginning of the list.
void	ft_lstadd_front(t_list **lst, t_list *new);

//	ft_lstsize:	Counts and returns the number of nodes in the list provided.
int		ft_lstsize(t_list *lst);

//	ft_lstlast:	Takes a list, searches and returns the last node in the list.
t_list	*ft_lstlast(t_list *lst);

//	ft_lstadd_back:	Takes a pointer to the address of the list's head node and
//					a new node, which it adds at the end of the list.
//					It returns nothing.
void	ft_lstadd_back(t_list **lst, t_list *new);

//	ft_lstdelone:	Takes a node, applies del to its content, relinks the list
//					 and frees the node, it returns nothing.
void	ft_lstdelone(t_list *lst, void (*del)(void *));

//	ft_lstclear:	Takes a pointer to the address of a node in a list, and
//					del which it applies to each successive node's content.
//					It frees the successive nodes as well and returns nothing.
void	ft_lstclear(t_list **lst, void (*del)(void *));

//	ft_lstiter:	Iterates a list, applying f to the contents of the
//				nodes of the list. returns nothing.
void	ft_lstiter(t_list *lst, void (*f)(void *));

//	ft_lstmap:	Iterates lst, applies f to it's contents, creates a new list
//				based on the actions of f. calls del on a content of a node
//				when necessary, and returns the allocated list.
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
