/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 08:08:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/05 15:50:16 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

static void	add_cmds(t_command *cmd, char **cmds, t_type type, char **env)
{
	t_commandlist	*new_node;

	new_node = (t_commandlist *)bin_malloc(sizeof(t_commandlist));
	if (!new_node)
		return ;
	new_node->cmd = cmds;
	new_node->files = NULL;
	new_node->type = type;
	new_node->env = env;
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
		if (start->type == INFILE || start->type == OUTFILE
			|| start->type == APPEND || start->type == HEREDOC)
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
		cmd[j++] = bin_strdup(start->lexeme);
		start = start->next;
	}
	cmd[j] = NULL;
	return (cmd);
}

static char	**find_lexemes(t_toklist **curr, t_type *type, int *redirection)
{
	int			i;
	t_type		t;
	char		**cmd;
	t_toklist	*start;

	i = 0;
	start = *curr;
	while (*curr)
	{
		t = (*curr)->type;
		if (t == PIPE || t == AND || t == OR)
			break ;
		else if (t == INFILE || t == OUTFILE || t == APPEND || t == HEREDOC)
			(*redirection)++;
		else if (t == D_QUOTE || *(*curr)->lexeme)
			i++;
		*curr = (*curr)->next;
	}
	if (!i)
		return (NULL);
	cmd = (char **)bin_malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	return (enter_cmd(start, curr, cmd, type));
}

void	join_cmd_and_args(t_command *cmd, t_toklist *tokens, char **env)
{
	t_type		type;
	t_toklist	*temp;
	int			redirection;
	char		**cmds_args;

	temp = tokens;
	while (tokens)
	{
		redirection = 0;
		type = NOTHING;
		cmds_args = find_lexemes(&tokens, &type, &redirection);
		if (cmds_args || redirection)
			add_cmds(cmd, cmds_args, type, env);
		if (tokens)
		{
			add_cmds(cmd, NULL, tokens->type, env);
			tokens = tokens->next;
		}
	}
	tokens = temp;
}
