/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/15 18:03:56 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parse.h"

t_toklist	*create_node(char *name)
{
	t_toklist	*new_node;

	new_node = (t_toklist *)malloc(sizeof(t_toklist));
	if (!new_node)
		return (NULL);
	new_node->name = name;
	new_node->type = 0;
	new_node->next = NULL;
	return (new_node);
}

void	add_token(t_toklist *token, t_tok_access *access)
{
	if (!access->head)
	{
		access->head = token;
		access->tail = token;
		return ;
	}
	access->tail->next = token;
	access->tail = token;
}

t_toklist	*scan_line(char *line)
{
	int				i;
	t_tok_access	tok_list;

	i = 0;
	tok_list.head = NULL;
	while (line[i])
	{
	}
	return (NULL);
}
