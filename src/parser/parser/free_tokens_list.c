/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 08:30:36 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 11:30:40 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/*
 * Frees the tokens list which it takes as arguments.
 */
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

/*
 * Frees the env list which it takes as argument.
 */
void	free_env_list(t_env *env)
{
	t_envlist	*curr;
	t_envlist	*tmp;

	curr = env->head;
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
