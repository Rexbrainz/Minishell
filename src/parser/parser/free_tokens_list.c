/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:30:36 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 18:12:21 by ndziadzi         ###   ########.fr       */
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

void	free_env_list(t_commandlist *cmd)
{
	t_envlist	*curr;
	t_envlist	*tmp;
	
	curr = cmd->env->head;
	tmp = NULL;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
