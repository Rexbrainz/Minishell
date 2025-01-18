/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/18 15:07:39 by sudaniel         ###   ########.fr       */
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
	tokens->lexemes_count++;
	return (true);
}

static bool	id_and_add_tokens(t_tokens *tokens, char **c)
{
	t_tokens	types;

	if (**c == '|' && !add_pipe_or_op(tokens, c))
		return (false);
	else if (**c == '\'')
		s_quoting_state(tokens, c);
	else if (**c == '"')
		d_quoting_state(tokens, c);
	else if (**c == '$')
		add_variable(tokens, c);
	else if ((**c == '(' || **c == ')') && !add_l_or_r_paren(tokens, c))
		return (false);
	else if (**c == '<' && !add_infile_or_heredoc(tokens, c))
		return (false);
	else if (**c == '>' && !add_outfile_or_append(tokens, c))
		return (false);
	else if (**c == '*' && !wild_state(tokens, c))
		return (false);
	else if (**c == '&' && *(*c + 1) == '&' && !add_and(tokens, c))
		return (false);
	return (true);
}

t_toklist	*scan_line(t_tokens *tokens)
{
	char	*p;
	int		start;
	int		current;
	t_type	type;

	tokens->t_input = ft_strtrim(tokens->user_input, " \t");
	if (!tokens->t_input)
		return (NULL);
	p = tokens->t_input;
	while (*p)
	{
		while (isspace(*p))
			p++;
		id_and_add_tokens(tokens, &p);
	}
	return (tokens->head);
}
