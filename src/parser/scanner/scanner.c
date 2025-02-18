/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/17 13:17:50 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*****************************************************************************
 * Takes the tokens list, tokens type, lexeme and position of the lexeme     *
 * int the input. With these parameters, it creates a node and adds them to  *
 * the tokens list.                                                          *
 * With the start position we calculate the end pos of the lexeme.           *
 * The function returns true on success and false if malloc fails.           *
 * ***************************************************************************/
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

/****************************************************************
 * Takes the addresses of the iterator in scanline in order to  *
 * modify it, and the tokens list to add the token to the list. *
 * Identifies tokens based on the current character and adds    *
 * them to the list of tokens.                                  *
 * It returns true if tokens addition is a success and false    *
 * when malloc fails, or perhaps in some cases failure due to   *
 * arrival of a sigint signal.                                  *
 * **************************************************************/
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

/**********************************************************************
 * Takes the tokens data struct to access the entered input, and      *
 * a pointer to a pointer to strings, which is used to iterate        *
 * the user input.                                                    *
 * It scans the input, get rid of white spaces and identifying tokens *
 * The function returns a pointer to the head of the list of tokens   *
 * created.                                                           *
 **********************************************************************/
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
