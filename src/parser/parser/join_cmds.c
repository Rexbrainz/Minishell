/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:08:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 09:17:40 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "parser.h"
//#include "scanner.h"

static void	add_cmds(t_command *cmd, char **cmds, t_type type)
{
	t_commandlist	*new_node;

	new_node = (t_commandlist *)malloc(sizeof(t_commandlist));
	if (!new_node)
		return ;
	new_node->cmd = cmds;
	new_node->files = NULL;
	new_node->type = type;
	new_node->next = NULL;
	if (!cmd->head)
	{
		cmd->head = new_node;
		cmd->tail = new_node;
	}
	else
	{
		cmd->tail->next = new_node;
		cmd->tail = new_node;
	}
	cmd->size++;
}

static char	**enter_cmd(t_toklist *start, t_toklist **end, char **cmd
		, t_type *type)
{
	int			j;

	j = 0;
	while (start != *end)
	{
		if (start->type == INFILES || start->type == OUTFILES
			|| start->type == APPENDS || start->type == HEREDOCS)
		{
			start = start->next;
			continue ;
		}
		if (start->type != D_QUOTE && !*start->lexeme)
		{
			start = start->next;
			continue ;
		}
		if (!j)
			*type = start->type;
		cmd[j++] = ft_strdup(start->lexeme);
		start = start->next;
	}
	cmd[j] = NULL;
	return (cmd);
}

static char	**find_lexemes(t_toklist **curr, t_type *type)
{
	int			i;
	char		**cmd;
	t_toklist	*start;

	i = 0;
	start = *curr;
	while (*curr)
	{
		if ((*curr)->type == PIPES || (*curr)->type == ANDS
			|| (*curr)->type == ORS)
			break ;
		if ((*curr)->type != INFILES && (*curr)->type != OUTFILES
			&& (*curr)->type != APPENDS && (*curr)->type != HEREDOCS)
		{
			if ((*curr)->type == D_QUOTE || *(*curr)->lexeme)
				i++;
		}
		*curr = (*curr)->next;
	}
	if (!i)
		return (NULL);
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	return (enter_cmd(start, curr, cmd, type));
}

void	join_cmd_and_args(t_command *cmd, t_toklist *tokens)
{
	t_type		type;
	t_toklist	*temp;
	char		**cmds_args;

	temp = tokens;
	while (tokens)
	{
		type = NOTHING;
		cmds_args = find_lexemes(&tokens, &type);
		if (cmds_args)
			add_cmds(cmd, cmds_args, type);
		if (tokens)
		{
			add_cmds(cmd, NULL, tokens->type);
			tokens = tokens->next;
		}
	}
	tokens = temp;
}
