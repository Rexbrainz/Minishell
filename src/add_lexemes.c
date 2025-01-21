/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:26:44 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/21 18:11:11 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

bool	add_pipe_or_op(t_tokens *tokens, char **c)
{
	char	*lexeme;

	if (*(*c + 1) == '|')
	{
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, ORS, lexeme, *c - tokens->t_input))
			return (false);
		*c += 2;
	}
	else
	{
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 1);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, PIPES, lexeme, *c - tokens->t_input))
			return (false);
		*c += 1;
	}
	return (true);
}

bool	add_infile_or_heredoc(t_tokens *tokens, char **c)
{
	char	*lexeme;
	int		len;

	if (*(*c + 1) == '<')
	{
		len = get_rest_of_lexeme(c, HEREDOCS);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, HEREDOCS, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_rest_of_lexeme(c, INFILES);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, INFILES, lexeme, *c - tokens->t_input))
			return (false);
	}
	*c += len;
	return (true);
}

bool	add_outfile_or_append(t_tokens *tokens, char **c)
{
	int		len;
	char	*lexeme;

	if (*(*c + 1) == '>')
	{
		len = get_rest_of_lexeme(c, APPENDS);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, APPENDS, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_rest_of_lexeme(c, OUTFILES);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, OUTFILES, lexeme, *c - tokens->t_input))
			return (false);
	}
	*c += len;
	return (true);
}

bool	add_variable(t_tokens *tokens, char **c)
{
	int		i;
	char	*s;
	t_type	type;
	char	*lexeme;

	if (*(*c + 1) == '(')
		type = CMD_SUB;
	else
		type = DOLLAR;
	s = *c;
	i = 0;
	while (*s && *s != ' ')
		if (*s++ == '(')
			i++;
	if (type == CMD_SUB)
		find_last_r_paren(&s, &i);
	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, s - *c);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, type, lexeme, *c - tokens->t_input))
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
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (!add_token(tokens, STAR, lexeme, s - tokens->t_input))
		return (false);
	return (true);
}
