/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 08:25:05 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

int	process_tokens(t_toklist *current)
{
	t_type			c_t;
	static t_type	l_t = NOTHING;

	c_t = current->type;
	if ((c_t == PIPES || c_t == ANDS || c_t == ORS)
		&& (l_t == NOTHING || l_t == c_t))
		return (258);
	else if (c_t == HEREDOCS)
		current->lexeme = get_heredoc_input(current->lexeme);
	else if (c_t == DOLLAR || c_t == D_QUOTE)
		current->lexeme = expand(current->lexeme);
	l_t = c_t;
	return (0);
}

t_tokens	*parse_line(t_command *cmd, t_tokens *tokens)
{
	t_type		t;
	t_toklist	*current;

	tokens->head = scan_line(tokens);
	current = tokens->head;
	while (current)
	{
		t = current->type;
		if ((t == PIPES || t == ANDS || t == ORS) && current == tokens->head)
			prompt1(tokens); // Find a solid way to handle more prompts.	
		if (t == HEREDOCS)
			current->lexeme = get_heredoc_input(current->lexeme);
		else if (t == DOLLAR || t == D_QUOTE)
			current->lexeme = expand(current->lexeme);
		current = current->next;
	}
	remove_escape_char(tokens);
	join_cmd_and_args(cmd, tokens->head);
	enter_filelist(cmd, tokens->head);
	return (tokens);
}
