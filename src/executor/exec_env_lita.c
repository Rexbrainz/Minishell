/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_lita.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:52:23 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 15:40:30 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*
	Flag if its a child process
	if so we need to clean memory
*/
void	clean_exit(int update, t_commandlist *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (update == NO_REDIRECTION)
	{
		exit_status = cmd->env->exit_status;
		free_env_list(cmd->env);
		rl_clear_history();
		bin_malloc(-1);
		exit(exit_status);
	}
}

/*
	saving only things needed for env
	omiting variables without values
*/
static int	get_proper_size(t_env *env)
{
	t_envlist	*current;
	int			size;

	current = env->head;
	size = 0;
	while (current != NULL)
	{
		if (current->value != NULL)
			size++;
		current = current->next;
	}
	return (size);
}

/*
	adding up strings to the matrix for env
	joining nodes from keys and the values
*/
static char	**populate_env(t_env *env, int size)
{
	char		**new_env;
	t_envlist	*current;
	int			array_c;

	array_c = 0;
	current = env->head;
	new_env = bin_malloc(sizeof(char **) * (size + 1));
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			new_env[array_c] = bin_strjoin(current->key, current->value);
			array_c++;
		}
		current = current->next;
	}
	new_env[array_c] = NULL;
	return (new_env);
}

/*
	Generating the env out export list
	keeping only the content with value
*/
char	**generate_env(t_env *env)
{
	char	**new_env;
	int		size;

	size = get_proper_size(env);
	new_env = populate_env(env, size);
	return (new_env);
}
