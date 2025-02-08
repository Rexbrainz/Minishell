/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:03:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/08 12:25:43 by sudaniel         ###   ########.fr       */
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

bool	add_backslash(t_tokens *tokens, char **c)
{
	char	*prev;
	char	*lexeme;
	char	*space;

	prev = *c - 1;
	space = *c + 2;
	if (*prev != ' ')
		tokens->backslash_inside_word = true;
	if (*space == ' ')
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 3);
	else
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme
		|| !add_token(tokens, BACK_SLASH, lexeme, *c - tokens->t_input))
		return (false);
	if (*space == ' ')
		*c += 3;
	else
		*c += 2;
	return (true);
}
