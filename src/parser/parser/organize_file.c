/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   organize_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 10:10:15 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 11:45:54 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/*
 * It creates and initializes a file list which it returns.
 */
static t_file	*init_files(void)
{
	t_file	*file;

	file = (t_file *)bin_malloc(sizeof(t_file));
	if (!file)
		return (NULL);
	file->head = NULL;
	file->tail = NULL;
	file->size = 0;
	return (file);
}

/* **********************************************************************
 * Takes a file list, filename (lexeme) and token type.                 *
 * Creates a node and initializes it with the above arguments and adds  *
 * the node to the list.                                                *
 * It returns true is successful else false if malloc fails.            *
 * **********************************************************************/
static bool	add_file(t_file *file, char *filename, t_type type)
{
	t_filelist	*new_node;

	new_node = (t_filelist *)bin_malloc(sizeof(t_filelist));
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

/* ******************************************************************
 * Takes the tokens list, and makes a file list for every           *
 * redirection token type found in a simple command (i.e commmands  *
 * separated by a pipeline or logical operators)                    *
 * It returns the file list created.                                *
 * ******************************************************************/
static t_file	*get_filelist(t_toklist **tokens)
{
	t_file	*file;

	file = NULL;
	while (*tokens)
	{
		if ((*tokens)->type == PIPE || (*tokens)->type == AND
			|| (*tokens)->type == OR)
			break ;
		if ((*tokens)->type == INFILE || (*tokens)->type == OUTFILE
			|| (*tokens)->type == APPEND || (*tokens)->type == HEREDOC)
		{
			if (!file)
				file = init_files();
			if (!file)
				return (NULL);
			add_file(file, bin_strdup((*tokens)->lexeme), (*tokens)->type);
		}
		*tokens = (*tokens)->next;
	}
	return (file);
}

/* ***********************************************************
 * Adds every files list created to the file list member of  *
 * the command list.                                         *
 * ***********************************************************/
void	enter_filelist(t_command *cmd, t_toklist *tokens)
{
	t_commandlist	*cmdlist;

	cmdlist = cmd->head;
	while (cmdlist)
	{
		if (cmdlist->type == PIPE || cmdlist->type == AND
			|| cmdlist->type == OR)
		{
			cmdlist = cmdlist->next;
			continue ;
		}
		cmdlist->files = get_filelist(&tokens);
		if (tokens)
			tokens = tokens->next;
		cmdlist = cmdlist->next;
	}
}
