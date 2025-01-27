/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:23:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/27 06:46:01 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scanner.h"
#include "../../../Includes/minishell.h"

static int	get_strlen_without_escaped_newlines(t_tokens *tokens, char **c);
static bool	process_dquote(t_tokens *tokens, char **c);

bool	add_and(t_tokens *tokens, char **c)
{
	char	*lexeme;	

	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, STAR, lexeme, *c - tokens->t_input))
		return (false);
	tokens->l_t = ANDS;
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
	tokens->l_t = type;
	*c += 1;
	return (true);
}

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
				prompt_for_more(tokens, c, &s);
		lexeme = ft_substr(tokens->t_input,
				s + 1 - tokens->t_input, *c - (s + 1));
		if (!lexeme || !add_token(tokens, S_QUOTE, lexeme, s - tokens->t_input))
			return (false);
	}
	else
		if (!process_dquote(tokens, c))
			return (false);
	tokens->l_t = type;
	return (*c += 1, true);
}

static bool	process_dquote(t_tokens *tokens, char **c)
{
	int		j;
	char	*s;
	int		len;
	char	*lexeme;

	s = *c;
	len = get_strlen_without_escaped_newlines(tokens, c);
	*c = s + 1;
	lexeme = (char *)malloc(len + 1);
	if (!lexeme)
		return (false);
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

static int	get_strlen_without_escaped_newlines(t_tokens *tokens, char **c)
{
	int	len;

	len = 0;
	(*c)++;
	while (**c != '"')
	{
		if (!**c)
			prompt_for_more(tokens, c, NULL);
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
