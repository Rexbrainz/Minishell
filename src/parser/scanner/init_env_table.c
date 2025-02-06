/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 17:50:13 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../scanner.h"
#include "../../../Includes/minishell.h"

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

	new_node = (t_envlist *)malloc(sizeof(t_envlist));
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
	char	*temp;

	s = NULL;
	s = ft_strchr(en, '=');
	if (!s)
	{
		*key = ft_strdup(en);
		*value = NULL;
	}
	else
	{
		*key = ft_substr(en, 0, s - en);
		*value = ft_strdup(s);
		if (!strncmp(*key, "SHLVL", ft_strlen(*key)))
		{
			env->shlvl = ft_atoi(*value + 1);
			env->shlvl++;
			free(*value);
			*value = ft_itoa(env->shlvl);
			temp = ft_strjoin("=", *value);
			free(*value);
			*value = temp;
		}
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
	return (true);
}
