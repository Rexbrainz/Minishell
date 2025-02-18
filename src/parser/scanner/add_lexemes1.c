/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:23:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 11:25:19 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ************************************************************************
 * Takes the tokens list and the address of a pointer to the user_input.  *
 * The && lexeme is extracted and entered into the list.                  *
 * The pointer is updated to point to the next char after the lexeme      *
 * The function returns true if successful and false if malloc fails.     *
 * ************************************************************************/
bool	add_and(t_tokens *tokens, char **c)
{
	char	*lexeme;	

	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, AND, lexeme, *c - tokens->t_input))
		return (false);
	*c += 2;
	return (true);
}

/* ************************************************************************
 * Takes the tokens list and the address of a pointer to the user_input.  *
 * The ( or ) lexeme is extracted and entered into the list.              *
 * The pointer is updated to point to the next char after the lexeme      *
 * The function returns true if successful and false if malloc fails.     *
 * ************************************************************************/
bool	add_l_or_r_paren(t_tokens *tokens, char **c)
{
	char	*lexeme;
	t_type	type;

	if (**c == ')')
		type = RIGHT_PAREN;
	else
		type = LEFT_PAREN;
	if (type == RIGHT_PAREN)
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 1);
	else
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 1);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, type, lexeme, *c - tokens->t_input))
		return (false);
	*c += 1;
	return (true);
}

/* **********************************************************************
 * Used by the process d_quote function to get the length of            *
 * the dquote lexeme without consecutive \ and \n chars.                *
 * If it does not find the matching closing dquote, it prompts for more *
 * The functon returns the length of the dquote lexeme.                 *
 * **********************************************************************/
static int
	get_strlen_without_escaped_newlines(t_tokens *tokens, char **c, char **s)
{
	int	len;

	len = 0;
	(*c)++;
	while (**c != '"')
	{
		if (!**c)
			if (!prompt_for_more(tokens, c, s))
				return (-1);
		if (**c == '\\' && *(*c + 1) == '"')
		{
			(*c)++;
			len++;
		}
		else if (**c == '\\' && *(*c + 1) == '\n')
		{
			*c += 2;
			continue ;
		}
		(*c)++;
		len++;
	}
	return (len);
}

/* *********************************************************************
 * Used by the add_literal function to extract double quote lexeme     *
 * and adds it to the tokens list. If there are consecutive \ and \n   * 
 * characters in the double quote, they are ignored and not included   *
 * in the double quote lexeme.                                         *
 * The function returns true if successful and false when malloc fails *
 * *********************************************************************/
static bool	process_dquote(t_tokens *tokens, char **c)
{
	int		j;
	char	*s;
	int		len;
	char	*lexeme;

	s = *c;
	len = get_strlen_without_escaped_newlines(tokens, c, &s);
	if (len == -1)
		return (false);
	*c = s + 1;
	lexeme = (char *)malloc(len + 1);
	j = 0;
	while (**c && j < len)
	{
		if (**c == '\\' && *(*c + 1) == '\n')
		{
			*c += 2;
			continue ;
		}
		lexeme[j++] = *(*c)++;
	}
	lexeme[j] = '\0';
	if (!add_token(tokens, D_QUOTE, lexeme, s - tokens->t_input))
		return (false);
	return (true);
}

/* ************************************************************************
 * Takes the tokens list and the address of a pointer to the user_input.  *
 * First it identifies the type of quote and extracts the lexeme until    *
 * the matching closing quote, which it adds to the tokens list.          *
 * It prompts for more if the closing matching quote is not found at end  *
 * of input.    														  *
 * The pointer is updated to point to the next char after the lexeme.     *
 * The function returns true if successful and false if malloc fails.     *
 * ************************************************************************/
bool	add_literal(t_tokens *tokens, char **c)
{
	char	*s;
	t_type	type;
	char	*lexeme;

	s = *c;
	if (**c == '\'')
		type = S_QUOTE;
	else
		type = D_QUOTE;
	if (type == S_QUOTE)
	{
		(*c)++;
		while (**c != *s)
			if (!*(*c)++)
				if (!prompt_for_more(tokens, c, &s))
					return (false);
		lexeme = ft_substr(tokens->t_input,
				s + 1 - tokens->t_input, *c - (s + 1));
		if (!lexeme || !add_token(tokens, S_QUOTE, lexeme, s - tokens->t_input))
			return (false);
	}
	else
		if (!process_dquote(tokens, c))
			return (false);
	return (*c += 1, true);
}
