/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:10:15 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/30 16:36:51 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

static t_file	*init_files(void)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->head = NULL;
	file->tail = NULL;
	file->size = 0;
	return (file);
}

static bool	add_file(t_file *file, char *filename, t_type type)
{
	t_filelist	*new_node;

	new_node = (t_filelist *)malloc(sizeof(t_filelist));
	if (!new_node)
		return (false);
	new_node->type = type;
	new_node->filename = filename;
	new_node->next = NULL;
	if (!file->head)
	{
		file->head = new_node;
		file->tail = new_node;
	}
	else
	{
		file->tail->next = new_node;
		file->tail = new_node;
	}
	file->size++;
	return (true);
}

static t_file	*get_filelist(t_toklist **tokens)
{
	t_file	*file;

	file = NULL;
	while (*tokens)
	{
		if ((*tokens)->type == PIPES || (*tokens)->type == ANDS
			|| (*tokens)->type == ORS)
			break ;
		if ((*tokens)->type == INFILES || (*tokens)->type == OUTFILES
			|| (*tokens)->type == APPENDS || (*tokens)->type == HEREDOCS)
		{
			if (!file)
				file = init_files();
			if (!file)
				return (NULL);
			add_file(file, (*tokens)->lexeme, (*tokens)->type);
		}
		*tokens = (*tokens)->next;
	}
	return (file);
}

void	enter_filelist(t_command *cmd, t_toklist *tokens)
{
	t_commandlist	*cmdlist;

	cmdlist = cmd->head;
	while (cmdlist)
	{
		cmd->head->files = get_filelist(&tokens);
		if (cmd->head->files)
			ft_printf("There is a file\n");
		else
			ft_printf("NONE\n");
		if (tokens)
			tokens = tokens->next;
		cmdlist = cmdlist->next;
	}
}
