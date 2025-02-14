/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:03:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/14 10:43:33 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

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

static t_type	get_b_slash_type(char c)
{
	if (!c)
		return (L_BACK_SLASH);
	return (BACK_SLASH);
}

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
