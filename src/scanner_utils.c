/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:26:44 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/16 17:09:38 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

void	init_tok_access(t_tok_access *tok_access, char *user_input)
{
	tok_access->head = NULL;
	tok_access->tail = NULL;
	tok_access->user_input = user_input;
	tok_access->lexemes_count = 0;
	tok_access->is_inside_dquote = false;
	tok_access->is_inside_squote = false;
	tok_access->size = 0;
}

bool	add_pipe_or_op(t_tok_access *tok_access, char **c)
{
	if (c == next_char)
		return (ORS);
	return (PIPE);
}

bool	add_infile_or_heredoc(t_tok_access *tok_access, char **c)
{
	if (c == next_char)
		return (HEREDOCS);
	return (INFILES);
}

bool	add_outfile_or_append(t_tok_access *tok_access, char **c)
{
	if (c == next_char)
		return (APPENDS);
	return (OUTFILES);
}
