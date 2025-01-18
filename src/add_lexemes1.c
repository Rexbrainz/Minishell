/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:23:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/18 15:50:28 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Includes/minishell.h"

bool	add_and(t_tokens *tokens, char **c)
{
	char	*lexeme;	

	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, STAR, lexeme, *c - tokens->t_input))
		return (false);
	*c += 2;
	return (true);
}

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

bool	d_quoting_st

/*
 * TODO
 * START: Find a simpler way.
 */
bool	s_quoting_state(t_tokens *tokens, char **c, int pos)
{
	char	*lexeme;
	char	*start;
	char	*temp;
	char	*s;
	int		len;

	lexeme = NULL;
	start = *c;
	if (lexeme)
		start = tokens->t_input + len + 1;
	s = start;
	while (*s && *s != '\'')
		s++;
	*c = s;
	temp = ft_substr(start, 0, s - start);
	if (!temp)
		return (false);
	if (lexeme)
	{
		start = lexeme;
		lexeme = ft_strjoin(lexeme, temp);
		if (!lexeme)
			return (false);
		free(start);
	}
	else
		lexeme = temp;
	if (!add_token(tokens, S_QUOTE, lexeme, pos))
		return (false);
	return (true);
}
