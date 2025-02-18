/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_adjacent_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:04:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 12:30:31 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* **************************************************************
 * Returns true if a token type is mergeable or not.            *
 * tokens type like PIPE, OR, AND or HEREDOC are not mergeable. *
 * **************************************************************/
static bool	is_mergeable(t_type t)
{
	if (t == WORD || t == OPTIONS || t == BUILTIN || t == DOLLAR
		|| t == CMD_SUB || t == D_QUOTE || t == S_QUOTE || t == STAR
		|| t == PID || t == EXIT_STAT || t == INFILE || t == OUTFILE
		|| t == APPEND)
		return (true);
	return (false);
}

/*
 * Merges two lexemes together and deletes the current node
 */
static void	merge(t_toklist *curr)
{
	t_toklist	*temp;
	char		*new_lexeme;

	new_lexeme = ft_strjoin(curr->lexeme, curr->next->lexeme);
	free(curr->lexeme);
	curr->lexeme = new_lexeme;
	curr->end_pos = curr->next->end_pos;
	temp = curr->next;
	curr->next = curr->next->next;
	free(temp->lexeme);
	free(temp);
}

/* ***********************************************************************
 * Takes the tokens list, interates through it, joins tokens             *
 * whose lexemes were previously not separated by a white space,         *
 * To do that it checks if the current token and the next are mergeable  *
 * or not. The function returns nothing.                                 *
 * ***********************************************************************/
void	merge_adjacent_tokens(t_tokens *tokens)
{
	int			diff;
	t_toklist	*curr;

	curr = tokens->head;
	while (curr)
	{
		diff = 0;
		if (curr->next)
		{
			if (is_mergeable(curr->type) && is_mergeable(curr->next->type))
			{
				diff = curr->next->start_pos - curr->end_pos;
				if (diff == 1)
				{
					merge(curr);
					continue ;
				}
			}
		}
		curr = curr->next;
	}
}
