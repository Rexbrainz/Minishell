/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:58:39 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/23 18:33:49 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
#include "scanner.h"
#include "parser.h"
/*
void	split_into_cmds(t_cmd *cmd, t_tokens *tokens)
{
	int	len;

	while (tokens->head)
	{
		while (	
	}
}
*/

static bool	add_file(t_files **files, char *file_name, t_type type)
{
	t_files	*new_file;
	t_files	*current;

	new_file = (t_files *)malloc(sizeof(t_files));
	if (!new_file)
		return (false);
	new_file->type = type;
	new_file->file_name = file_name;
	new_file->next = NULL;
	if (!*files)
		*files = new_file;
	else
	{
		current = *files;
		while (current->next)
			current = current->next;
		current->next = new_file;
	}
	return (true);
}

t_files	*get_cmd_file_list(t_cmd cmd, t_tokens *tokens)
{
	t_type		type;
	t_files		*files;
	t_cmd		current;;
	char		*file_name;

	current = cmd->head;
	while (current)
	{
		while (tokens->head)
		{
			type = tokens->head->type;
			if (type == PIPES || type == ANDS || type == ORS)
				break ;
			if (type == APPENDS || type == OUTFILES || type == INFILES
				|| type == HEREDOCS)
			{
				file_name = get_file_name(tokens->lexeme);
				if (!add_file(current_cmd->files, file_name, type))
					return (false);
			}
			current = current->next;
		}
		current = current->next;
	}
	return (files);
}
