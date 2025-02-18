/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:26:44 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 16:14:39 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ***************************************************************************
 * Takes the tokens list and an address to a pointer to the user_input.      *
 * If the next character is |, the lexeme is extracted as an OR operator     *
 * and added into the tokens list, else the lexeme is extracted as a pipe    *
 * and added into the tokens list.                                           *
 * The function returns true when successful and false if malloc fails.      *
 * ***************************************************************************/
bool	add_pipe_or_op(t_tokens *tokens, char **c)
{
	char	*lexeme;

	if (*(*c + 1) == '|')
	{
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, OR, lexeme, *c - tokens->t_input))
			return (false);
		*c += 2;
	}
	else
	{
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 1);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, PIPE, lexeme, *c - tokens->t_input))
			return (false);
		*c += 1;
	}
	return (true);
}

/* ***************************************************************************
 * Takes the tokens list and an address to a pointer to the user_input.      *
 * If the next character is <, the heredoc delimeter (lexeme) is extracted   *
 * and added into the tokens list, else the INFILE filename (lexeme) is      *
 * extracted and added into the tokens list.                                 *
 * The pointer is updated to point to the character after the lexeme end_pos *
 * The function returns true when successful and false if malloc fails.      *
 * ***************************************************************************/
bool	add_infile_or_heredoc(t_tokens *tokens, char **c)
{
	char	*lexeme;
	int		len;

	if (*(*c + 1) == '<')
	{
		len = get_heredoc_delim_len(c);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme
			|| !add_token(tokens, HEREDOC, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_filelen(c, INFILE);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, INFILE, lexeme, *c - tokens->t_input))
			return (false);
	}
	*c += len;
	return (true);
}

/* ***************************************************************************
 * Takes the tokens list and an address to a pointer to the user_input.      *
 * If the next character is >, the APPEND filename (lexeme) is extracted     *
 * and added into the tokens list, else the OUTFILE filename (lexeme) is     *
 * extracted and added into the tokens list.                                 *
 * The pointer is updated to point to the character after the lexeme end_pos *
 * The function returns true when successful and false if malloc fails.      *
 * ***************************************************************************/
bool	add_outfile_or_append(t_tokens *tokens, char **c)
{
	int		len;
	char	*lexeme;

	if (*(*c + 1) == '>')
	{
		len = get_filelen(c, APPEND);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, APPEND, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_filelen(c, OUTFILE);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, OUTFILE, lexeme, *c - tokens->t_input))
			return (false);
	}
	*c += len;
	return (true);
}

/* *********************************************************************
 * Takes the tokens list and address to a pointer to the user_input.   *
 * the next character tells us what token type it is and depending     *
 * on what token type it is we extract the lexeme and add it to the    *
 * tokens list. The pointer is updated to point to the char after the  *
 * lexeme end_pos. The function returns false if malloc fails else true *
 * ******************************************************************** */
bool	add_variable(t_tokens *tokens, char **c)
{
	char	*s;
	t_type	type;
	char	*lexeme;

	type = get_type(*c + 1);
	s = *c;
	if (type == WORD)
		find_eot(tokens, c, &s, WORD);
	else if (type == CMD_SUB)
		find_eot(tokens, c, &s, CMD_SUB);
	else if (type == DOLLAR)
		find_eot(tokens, c, &s, DOLLAR);
	else if (type == EXIT_STAT)
		s = *c + 2;
	else
		s = *c + 2;
	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, s - *c);
	if (!lexeme || !add_token(tokens, type, lexeme, *c - tokens->t_input))
		return (false);
	*c = s;
	return (true);
}

/* *********************************************************************
 * Takes the tokens list and address to a pointer to the user_input.   *
 * The pointer is used to find the end of the lexeme, another pointer  *
 * is used to track back to find the lexeme start before the * char.   *
 * The lexeme is extracted and entered into the token list.            *
 * The function returns false if malloc fails and true when successful *
 * *********************************************************************/
bool	wild_state(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	while (*s && *(s - 1) != ' ')
		s--;
	while (**c && **c != ' ')
		(*c)++;
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, STAR, lexeme, s - tokens->t_input))
		return (false);
	return (true);
}
