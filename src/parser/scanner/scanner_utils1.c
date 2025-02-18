/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 07:21:46 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ************************************************************************
 * A utility function for cases when more input is needed from the user.  *
 * It takes the tokens data struct, two addresses of pointers.            *
 * c points to the user_input in tokens->t_input, s can be NULL,          *
 * when not NULL it is used as an iterator from c which points to the     *
 * null terminator signifying incompleteness of the current lexeme.       *
 * The function prompts for more input, and reassigs c and s to the index *
 * they were previously pointing in the newly modified input.        	  *
 * In addition a handler for SIGINT is installed, returning NULL helps    *
 * us handle SIGINT, otherwise, the newly modified input is returned.     *
 * ************************************************************************/
char	*prompt_for_more(t_tokens *tokens, char **c, char **s)
{
	int	c_len;
	int	s_len;

	signal(SIGINT, heredoc_sigint_handler);
	c_len = ft_strlen(tokens->t_input);
	if (s)
		s_len = *s - tokens->t_input;
	if (!prompt1(tokens))
	{
		signal(SIGINT, main_sigint_handler);
		return (NULL);
	}
	*c = tokens->t_input + c_len;
	if (s)
		*s = tokens->t_input + s_len;
	return (tokens->t_input);
}

/* ********************************************************************
 * A utility function for handling redirection tokens in add_lexeme.c *
 * Takes the address of a pointer to the user_input, and the token    *
 * type. If the type is APPEND the pointer is shifted an index ahead. *
 * It ignores all spaces when there is one after the redirection      *
 * character. From there it finds the end of the lexeme (filename).   *
 * The function returns the length of the filename.                   *
 * ********************************************************************/
int	get_filelen(char **c, t_type type)
{
	char	*s;

	(*c)++;
	if (type == APPEND)
		(*c)++;
	while (**c && ft_isspace(**c))
		(*c)++;
	s = *c;
	while (*s && !is_delim(*s))
		s++;
	return (s - *c);
}

/*
 * Returns true if the char c is identified as a delimeter, else false.
 */
bool	is_delim(char c)
{
	if (ft_isspace(c) || c == ')' || c == '(' || c == '"'
		|| c == '\'' || c == '|' || c == '&' || c == '$'
		|| c == '<' || c == '>' || c == '\\')
		return (true);
	return (false);
}
