/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/30 07:48:38 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"
/*
bool	add_cmd(t_cmd *cmd, char **cmd_args, t_type type, t_files *files)
{
	t_cmds	*cmds;

	cmds = (t_cmds *)malloc(sizeof(t_cmds));
	if (!cmds)
		return (false);
	cmds->cmd = cmd_args;
	cmds->type = type;
	cmds->files = files;
	cmds->next = NULL;
	if (!cmd->head)
	{
		cmd->head = cmds;
		cmd->tail = cmds;
	}
	else
	{
		cmd->tail->next = cmds;
		cmd->tail = cmds;
	}
	return (true);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->size = 0;
	cmd->head = NULL;
	cmd->tail = NULL;
}

static void	organize_cmds(t_tokens *tokens)
{
	t_cmd	cmd;

	init_cmd(&cmd);
	split_into_cmds(&cmd, tokens);
//	return (&cmd);
}
*/
t_tokens	*parse_line(t_command *cmd, t_tokens *tokens)
{
	t_type		t;
	t_toklist	*current;
	//t_toklist	*prev;

	tokens->head = scan_line(tokens);
	//prev = NULL;
	current = tokens->head;
	while (current)
	{
		t = current->type;
		if (t == HEREDOCS)
			current->lexeme = get_heredoc_input(current->lexeme);
		else if (t == DOLLAR || t == D_QUOTE)
			//if (prev && prev->type != BACK_SLASH)
			current->lexeme = expand(current->lexeme);
		//prev = current;
		current = current->next;
	}
	remove_escape_char(tokens);
	join_cmd_and_args(cmd, tokens->head);
//	organize_cmds(tokens);
	return (tokens);
}
