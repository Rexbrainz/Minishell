/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 12:07:11 by sudaniel         ###   ########.fr       */
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
	if ((c_t == PIPE || c_t == AND || c_t == OR)
		&& (l_t == NOTHING || l_t == c_t))
		return (258);
	else if (c_t == HEREDOC)
		current->lexeme = get_heredoc_input(current->lexeme);
	else if (c_t == DOLLAR || c_t == D_QUOTE)
		current->lexeme = expand(current->lexeme);
	l_t = c_t;
	return (0);
}

t_tokens	*parse_line(t_command *cmd, t_tokens *tokens, char **env)
{
	t_type		t;
	t_toklist	*current;

	tokens->head = scan_line(tokens);
	current = tokens->head;
	while (current)
	{
		t = current->type;
		if ((t == PIPE || t == AND || t == OR) && current == tokens->head)
			prompt1(tokens); // Find a solid way to handle more prompts.	
		if (t == HEREDOC)
			current->lexeme = get_heredoc_input(current->lexeme);
		else if (t == DOLLAR || t == D_QUOTE)
			current->lexeme = expand(current->lexeme);
		current = current->next;
	}
	remove_escape_char(tokens);
	join_cmd_and_args(cmd, tokens->head, env);
	enter_filelist(cmd, tokens->head);
	return (tokens);
}
