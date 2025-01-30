/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:08:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/30 08:49:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
//#include "parser.h"
//#include "scanner.h"

static void	add_cmds(t_commandlist **head, t_commandlist **tail
		, char **cmds, t_type type)
{
	t_commandlist	*new_node;

	new_node = (t_commandlist *)malloc(sizeof(t_commandlist));
	if (!new_node)
		return ;
	new_node->cmd = cmds;
	new_node->files = NULL;
	new_node->type = type;
	new_node->next = NULL;
	if (!*head)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

static char	**enter_cmd(t_toklist *start, t_toklist *prev, t_toklist **end
		, char **cmd)
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
			prev = start;
			start = start->next;
			continue ;
		}
		cmd[j++] = ft_strdup(start->lexeme);
		prev = start;
		start = start->next;
	}
	cmd[j] = NULL;
	if (*end)
		*end = prev;
	return (cmd);
}

static char	**find_lexemes(t_toklist **curr, t_type *type)
{
	int			i;
	char		**cmd;
	t_toklist	*start;
	t_toklist	*prev;

	i = 0;
	*type = (*curr)->type;
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
	cmd = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	return (prev = start, enter_cmd(start, prev, curr, cmd));
}

void	join_cmd_and_args(t_command *cmd, t_toklist *curr)
{
	t_type		type;
	t_toklist	*temp;
	char		**cmds_args;

	temp = curr;
	while (curr)
	{
		type = -10;
		cmds_args = find_lexemes(&curr, &type);
		add_cmds(&cmd->head, &cmd->tail, cmds_args, type);
		if (curr)
			curr = curr->next;
	}
	curr = temp;
}
