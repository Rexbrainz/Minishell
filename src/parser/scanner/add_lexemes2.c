/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:03:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 11:26:14 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ****************************************************************************
 * Takes the tokens list and an address of a pointer to the user_input        *
 * It searches for the end of the lexeme, extracts the lexeme, and checks     *
 * if the extracted lexeme can be identified as a builtin, if so, the         *
 * lexeme is added to the tokens list as a builtin, else it is added as       *
 * a WORD.                                                                    *
 * ****************************************************************************/
bool	add_word_or_builtin(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	if (*s == '$')
		(*c)++;
	while (**c && !is_delim(**c))
		(*c)++;
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (is_builtin(lexeme))
	{
		if (!add_token(tokens, BUILTIN, lexeme, s - tokens->t_input))
			return (false);
	}
	else
		if (!add_token(tokens, WORD, lexeme, s - tokens->t_input))
			return (false);
	return (true);
}

/* ****************************************************************************
 * Takes the tokens list and address of a pointer pointing to the user_input  *
 * It searches for the end of the option lexeme, it checks if there are       *
 * multiple options and takes them as part of the lexeme. It extracts the     *
 * lexeme afterwards and adds it to the tokens list.     					  *
 * Updates the pointer to point to the char after the lexeme.                 *
 * It returns true if it successfully extracted the lexeme and adds it to     *
 * the tokens list.															  *
 * ****************************************************************************/
bool	add_options(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	while (*s && !is_delim(*s))
	{
		if (*s++ == ' ')
		{
			while (ft_isspace(*s))
				s++;
			if (*s != '-')
				break ;
		}
	}
	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, s - *c);
	if (!lexeme || !add_token(tokens, OPTIONS, lexeme, *c - tokens->t_input))
		return (false);
	*c = s;
	return (true);
}

/* **************************************************************************
 * A utility function to help check the surrounding characters around the   *
 * \ char.                                                                  *
 * The function returns nothing.                                            *
 * **************************************************************************/
static void	check_prev_and_space(t_tokens *tokens,
	char **c, char **prev, char **space)
{
	*prev = NULL;
	*space = NULL;
	if (*c != tokens->t_input)
		*prev = (*c - 1);
	if (*(*c + 1) && *(*c + 2))
		*space = *c + 2;
}

/* ********************************************************************
 * Returns a backslash type L_BACK_SLASH if c is the null terminator  *
 * else returns BACK_SLASH.                                           *
 * ********************************************************************/
static t_type	get_b_slash_type(char c)
{
	if (!c)
		return (L_BACK_SLASH);
	return (BACK_SLASH);
}

/* ************************************************************************
 * Takes the tokens list and an address to the pointer to the user_input. *
 * First it tries to identify if the backslash is the last in the input   *
 * or it simply escapes a character. Then it tries to check the           *
 * surrounding characters around this backslash to know if it is part     *
 * of other lexeme or characters (backslashes aren't part of standard     *
 * tokens for minishell). Afterwards the lexeme is extracted and          *
 * entered into the list. The pointer is updated to point to the start    *
 * of the next lexeme. The function returns true when successful and      *
 * false when malloc fail.                                                *
 * ************************************************************************/
bool	add_backslash(t_tokens *tokens, char **c)
{
	t_type	type;
	char	*prev;
	char	*lexeme;
	char	*space;

	type = get_b_slash_type(*(*c + 1));
	check_prev_and_space(tokens, c, &prev, &space);
	if (prev && *prev != ' ')
		tokens->backslash_inside_word = true;
	if (space && *space == ' ')
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 3);
	else if (*(*c + 1))
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	else
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 1);
	if (!lexeme
		|| !add_token(tokens, type, lexeme, *c - tokens->t_input))
		return (false);
	if (space && *space == ' ')
		*c += 3;
	else
		*c += 2;
	if (type == L_BACK_SLASH)
		*c += 1;
	return (true);
}
