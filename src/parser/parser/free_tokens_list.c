/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:30:36 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 11:02:13 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

void	free_tokens_list(t_tokens *tokens)
{
	t_toklist	*temp;

	temp = NULL;
	while (tokens->head)
	{
		free(tokens->head->lexeme);
		temp = tokens->head;
		tokens->head = tokens->head->next;
		free(temp);
	}
}

void	free_cmds_list(t_command *cmd)
{
	t_filelist		*red;
	t_commandlist	*temp;

	temp = NULL;
	while (cmd->head)
	{
		if (cmd->head->cmd)
		{
			while (*(cmd->head->cmd))
				free(*(cmd->head->cmd)++);
		}
		red = NULL;
		if (cmd->head->files)
		{
			while (cmd->head->files->head)
			{
				red = cmd->head->files->head;
				cmd->head->files->head = cmd->head->files->head->next;
				free(red);
			}
		}
		temp = cmd->head;
		cmd->head = cmd->head->next;
		free(temp);
	}
}
