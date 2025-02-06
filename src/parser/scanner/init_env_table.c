/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 16:47:51 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../scanner.h"
#include "../../../Includes/minishell.h"
/*
void	init_tokens(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->t_input = NULL;
	tokens->lexeme_count = 0;
	tokens->is_inside_squote = false;
	tokens->is_inside_dquote = false;
	tokens->backslash_inside_word = false;
}

void	init_commands(t_command *cmd)
{
	cmd->head = NULL;
	cmd->tail = NULL;
	cmd->size = 0;
}
*/

static void	init_environment(t_env *env)
{
	env->size = 0;
	env->shlvl = 0;
	env->head = NULL;
	env->tail = NULL;
}

static bool	add_env_var(t_env *env, char *key, char *value)
{
	t_envlist	*new_node;

	new_node = (t_envlist *)bin_malloc(sizeof(t_envlist));
	if (!new_node)
		return (false);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (!env->head)
	{
		env->head = new_node;
		env->tail = new_node;
	}
	else
	{
		env->tail->next = new_node;
		env->tail = new_node;
	}
	env->size++;
	return (true);
}

static void	get_key_and_value(t_env *env, char **key, char **value, char *en)
{
	char	*s;

	s = NULL;
	s = ft_strchr(en, '=');
	if (!s)
	{
		*key = bin_strdup(en);
		*value = NULL;
	}
	else
	{
		*key = bin_substr(en, 0, s - en);
		*value = bin_strdup(s);
		if (!strncmp(*key, "SHLVL", ft_strlen(*key)))
			env->shlvl = ft_atoi(*value);
	}
}

bool	init_env(t_env *env, char **en)
{
	int		i;
	char	*key;
	char	*value;

	init_environment(env);
	i = 0;
	key = NULL;
	value = NULL;
	while (en[i])
	{
		get_key_and_value(env, &key, &value, en[i]);
		if (!add_env_var(env, key, value))
			return (false);
		i++;
	}
	env->shlvl++;
	return (true);
}
