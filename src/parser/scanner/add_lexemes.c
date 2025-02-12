/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:26:44 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/12 10:46:44 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "../scanner.h"

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

bool	add_infile_or_heredoc(t_tokens *tokens, char **c)
{
	char	*lexeme;
	int		len;

	if (*(*c + 1) == '<')
	{
		len = get_rest_of_lexeme(c++, HEREDOC);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme
			|| !add_token(tokens, HEREDOC, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_rest_of_lexeme(c++, INFILE);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		ft_printf("%s\n", lexeme);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, INFILE, lexeme, *c - tokens->t_input))
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
		len = get_rest_of_lexeme(c++, APPEND);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, APPEND, lexeme, *c - tokens->t_input))
			return (false);
	}
	else
	{
		len = get_rest_of_lexeme(c++, OUTFILE);
		lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, len);
		if (!lexeme)
			return (false);
		if (!add_token(tokens, OUTFILE, lexeme, *c - tokens->t_input))
			return (false);
	}
	*c += len;
	return (true);
}

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
	return (*c = s, true);
}

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
