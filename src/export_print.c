/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:20:26 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/07 18:40:45 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

void	print_vars(t_commandlist *cmd, int update)
{
	char		*temp;
	t_envlist	*curr;

	curr = cmd->env->head;
	while (curr)
	{
		if (curr->value)
		{
			temp = curr->value;
			curr->value = ft_strjoin("\"", temp + 1);
			free(temp);
			temp = curr->value;
			curr->value = ft_strjoin(temp, "\"");
			free(temp);
			temp = curr->value;
			curr->value = ft_strjoin("=", temp);
			free(temp);
			ft_printf("declare -x %s%s\n", curr->key, curr->value);
		}
		else
			ft_printf("declare -x %s\n", curr->key);
		curr = curr->next;
	}
	clean_exit(update, cmd);
}
