/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:03:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 12:10:36 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "../scanner.h"

bool	add_word_or_builtin(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	if (*s == '$')
		(*c)++;
	while (**c && !is_delim(**c) && **c != '$')
		(*c)++;
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (is_builtin(lexeme))
	{
		if (!add_token(tokens, BUILTIN, lexeme, s - tokens->t_input))
			return (false);
		tokens->l_t = BUILTIN;
	}
	else
	{
		if (!add_token(tokens, WORD, lexeme, s - tokens->t_input))
			return (false);
		tokens->l_t = WORD;
	}
	return (true);
}

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
	tokens->l_t = OPTIONS;
	*c = s;
	return (true);
}

bool	add_backslash(t_tokens *tokens, char **c)
{
	char	*lexeme;
	char	*space;

	space = *c + 2;
	if (*space == ' ')
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 3);
	else
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme
		|| !add_token(tokens, BACK_SLASH, lexeme, *c - tokens->t_input))
		return (false);
	tokens->l_t = BACK_SLASH;
	if (*space == ' ')
		*c += 3;
	else
		*c += 2;
	return (true);
}
