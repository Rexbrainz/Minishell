/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:26:44 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 16:19:03 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

bool	add_pipe_or_op(t_tokens *tokens, char **c)
{
	char	*lexeme;

	if (**(c + 1) == '|')
	{
		lexeme = ft_substr(tokens->user_input, *c - tokens->user_input, 2);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, ORS, lexeme, *c++ - tokens->user_input))
			return (false);
	}
	else
	{
		lexeme = ft_substr(tokens->user_input, *c - tokens->user_input, 1);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, PIPES, lexeme, *c++ - tokens->user_input))
			return (false);
	}
	return (true);
}

bool	add_infile_or_heredoc(t_tokens *tokens, char **c)
{
	char	*lexeme;
	char	*s;
	int		len;

	if (*(*c + 1) == '<')
	{
		s = *c;
		len = get_rest_of_lexeme(c);
		lexeme = ft_substr(tokens->user_input, s - tokens->user_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, HEREDOCS, lexeme, s - tokens->user_input))
			return (false);
	}
	else
	{
		s = *c;
		len = get_rest_of_lexeme(c);
		lexeme = ft_substr(tokens->user_input, s - tokens->user_input, 1);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, INFILES, lexeme, s - tokens->user_input))
			return (false);
	}
	return (true);
}

bool	add_outfile_or_append(t_tokens *tokens, char **c)
{
	char	*lexeme;
	char	*s;
	int		len;

	if (*(*c + 1) == '>')
	{
		s = *c;
		len = get_rest_of_lexeme(c);
		lexeme = ft_substr(tokens->user_input, s - tokens->user_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, APPENDS, lexeme, *c - tokens->user_input))
			return (false);
	}
	else
	{
		s = *c;
		len = get_rest_of_lexeme(c);
		lexeme = ft_substr(tokens->user_input, s - tokens->user_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, OUTFILES, lexeme, s - tokens->user_input))
			return (false);
	}
	return (true);
}

bool	add_variable(t_tokens *tokens, char **c)
{
	char	*lexeme;
	char	*s;
	t_type	type;

	if (*(*c + 1) == '(')
		type = CMD_SUB;
	else
		type = DOLLAR;
	s = *c;
	while (*s != ' ')
		s++;
	if (type == CMD_SUB)
	{
		s = ft_strchr(s, ')');
		if (!s)
			return (false);
		++s;
	}
	lexeme = ft_substr(tokens->user_input, *c - tokens->user_input, s - *c);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, type, lexeme, *c - tokens->user_input))
		return (false);
	*c = s;
	return (true);
}

bool	wild_state(t_tokens *tokens, char **c)
{
	char	*lexeme;
	char	*s;

	s = *c;
	while (*s && *(s - 1) != ' ')
		s--;
	while (**c && **c != ' ')
		(*c)++;
	lexeme = ft_substr(tokens->user_input,
			s - tokens->user_input, (*c - 1) - s);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, STAR, lexeme, s - tokens->user_input))
		return (false);
	return (true);
}
