/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/31 10:34:57 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

t_tokens	*parse_line(t_command *cmd, t_tokens *tokens)
{
	t_type		t;
	t_toklist	*current;

	tokens->head = scan_line(tokens);
	current = tokens->head;
	while (current)
	{
		t = current->type;
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
