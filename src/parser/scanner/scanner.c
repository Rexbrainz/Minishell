/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 16:01:25 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
//#include "../parser.h"

bool	add_token(t_tokens *tokens, t_type types, char *lexeme, int s_pos)
{
	t_toklist	*new_node;

	new_node = (t_toklist *)malloc(sizeof(t_toklist));
	if (!new_node)
		return (false);
	new_node->lexeme = lexeme;
	new_node->type = types;
	new_node->lexeme_len = ft_strlen(lexeme);
	new_node->start_pos = s_pos;
	new_node->end_pos = s_pos + new_node->lexeme_len - 1;
	if (types == S_QUOTE || types == D_QUOTE)
		new_node->end_pos = s_pos + new_node->lexeme_len + 2 - 1;
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
	return (true);
}

static bool	id_and_add_tokens(t_tokens *tokens, char **c)
{
	if ((**c == '-') && !add_options(tokens, c))
		return (false);
	else if (**c == '\\' && !add_backslash(tokens, c))
		return (false);
	else if (**c == '|' && !add_pipe_or_op(tokens, c))
		return (false);
	else if ((**c == '\'' || **c == '"') && !add_literal(tokens, c))
		return (false);
	else if (**c == '*' && !wild_state(tokens, c))
		return (false);
	else if (**c == '$' && !add_variable(tokens, c))
		return (false);
	else if ((**c == '(' || **c == ')') && !add_l_or_r_paren(tokens, c))
		return (false);
	else if (**c == '<' && !add_infile_or_heredoc(tokens, c))
		return (false);
	else if (**c == '>' && !add_outfile_or_append(tokens, c))
		return (false);
	else if (**c == '&' && *(*c + 1) == '&' && !add_and(tokens, c))
		return (false);
	else if (**c && !is_delim(**c) && !add_word_or_builtin(tokens, c))
		return (false);
	return (true);
}

t_toklist	*scan_line(t_tokens *tokens, char **s)
{
	while (**s)
	{
		while (ft_isspace(**s))
			(*s)++;
		if (ft_isalnum(**s))
		{
			if (!add_word_or_builtin(tokens, s))
				return (NULL);
			continue ;
		}
		if (!id_and_add_tokens(tokens, s))
			return (NULL);
	}
	return (tokens->head);
}
