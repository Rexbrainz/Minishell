/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/20 14:32:30 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

//t_toklist	*create_node(char *name)
bool	add_token(t_tokens *tokens, t_type types, char *token, int s_pos)
{
	t_toklist	*new_node;

	new_node = (t_toklist *)malloc(sizeof(t_toklist));
	if (!new_node)
		return (false);
	new_node->lexeme = token;
	new_node->type = types;
	new_node->start_pos = s_pos;
	new_node->next = NULL;
	if (!tokens->head)
	{
		tokens->head = new_node;
		tokens->tail = new_node;
	}
	else
	{
		tokens->tail->next = new_node;
		tokens->tail = new_node;
	}
	tokens->lexeme_count++;
	tokens->size++;
	return (true);
}

static bool	id_and_add_tokens(t_tokens *tokens, char **c)
{
	char	*p;

	p = *c - 1;
	if (**c == '|' && *p != '\\' && !add_pipe_or_op(tokens, c))
		return (false);
	else if ((**c == '\'' || **c == '"')
		&& *p != '\\' && !add_literal(tokens, c))
		return (false);
	else if (**c == '$' && *p != '\\' && !add_variable(tokens, c))
		return (false);
	else if ((**c == '(' || **c == ')')
		&& *p != '\\' && !add_l_or_r_paren(tokens, c))
		return (false);
	else if (**c == '<' && *p != '\\' && !add_infile_or_heredoc(tokens, c))
		return (false);
	else if (**c == '>' && *p != '\\' && !add_outfile_or_append(tokens, c))
		return (false);
	else if (**c == '*' && *p != '\\' && !wild_state(tokens, c))
		return (false);
	else if (**c == '&' && *(*c + 1) == '&'
		&& *p != '\\' && !add_and(tokens, c))
		return (false);
	return (true);
}

static bool	add_word_or_builtin(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	while (**c != ' ')
		(*c)++;
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (is_builtin(lexeme))
	{
		if (!add_token(tokens, BUILTINS, lexeme, s - tokens->t_input))
			return (false);
	}
	else
		if (!add_token(tokens, WORDS, lexeme, s - tokens->t_input))
			return (false);
	return (true);
}

t_toklist	*scan_line(t_tokens *tokens)
{
	char	*s;

	tokens->t_input = ft_strtrim(tokens->user_input, " \t");
	if (!tokens->t_input)
		return (NULL);
	s = tokens->t_input;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (ft_isalnum(*s))
		{
			if (!add_word_or_builtin(tokens, &s))
				return (NULL);
			continue ;
		}
		if (!id_and_add_tokens(tokens, &s))
			return (NULL);
	}
	return (tokens->head);
}
