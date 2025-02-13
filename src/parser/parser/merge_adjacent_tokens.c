/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_adjacent_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 12:04:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/12 13:48:08 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static bool	is_mergeable(t_type t)
{
	if (t == WORD || t == OPTIONS || t == BUILTIN || t == DOLLAR
		|| t == CMD_SUB || t == D_QUOTE || t == S_QUOTE || t == STAR
		|| t == PID || t == EXIT_STAT || t == INFILE || t == OUTFILE
		|| t == APPEND)
		return (true);
	return (false);
}

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
