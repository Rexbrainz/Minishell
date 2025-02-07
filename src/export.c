/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:27:42 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/07 18:40:23 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

static void	enter_var(t_env *env, char *key, char *value)
{
	t_envlist	*curr;

	curr = env->head;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			if (!curr->value)
				curr->value = value;
			else
			{
				if (!value)
					return ;
				curr->value = value;
			}
		}
		curr = curr->next;
	}
	add_env_var(env, key, value);
}

static void	concatenate_var(t_env *env, char *key, char *value)
{
	char		*temp;
	t_envlist	*curr;

	curr = env->head;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key)))
		{
			if (!curr->value)
				curr->value = value;
			else
			{
				if (!value)
					return ;
				temp = curr->value;
				curr->value = ft_strjoin(temp, value + 1);
				free(temp);
				free(value);
				return ;
			}
		}
		curr = curr->next;
	}
	add_env_var(env, key, value);
}

static bool	get_key_and_value(char *env, char **key, char **value)
{
	char	*s;
	int		len;
	char	*temp;

	s = NULL;
	s = ft_strchr(env, '=');
	if (!s)
		*key = ft_strdup(env);
	else
	{
		*key = ft_substr(env, 0, s - env);
		len = ft_strlen(s);
		if (*(s + 1) == '"' && *(s + len - 1) == '"')
		{
			*value = ft_substr(s, 2, len - 2);
			temp = *value;
			*value = ft_strjoin("=", temp);
			free(temp);
		}
		else
			*value = ft_strdup(s);
	}
	if (ft_strchr(env, '+'))
		return (true);
	return (false);
}

static bool	check_syntax(t_commandlist *cmd, char *var, int update)
{
	if (*var != '_' || !ft_isalpha(*var))
	{
		write(2, "bash: export: `", 15);
		write(2, var, ft_strlen(var));
		write(2, "': not a valid identifier\n", 26);
		clean_exit(update, cmd);
		return (false);
	}
	while (*var && (*var != '+' || *var != '='))
	{
		if (*var != '_' || !ft_isalnum(*var))
		{
			write(2, "bash: export: `", 15);
			write(2, var, ft_strlen(var));
			write(2, "': not a valid identifier\n", 26);
			clean_exit(update, cmd);
			return (false);
		}
		var++;
	}
	return (true);
}

bool	export(t_commandlist *cmd, char **en, int update)
{
	int			i;
	char		*s;
	char		*key;
	char		*value;

	i = 1;
	if (!cmd->cmd[i])
	{
		print_vars(cmd, update);
		return (true);
	}
	while (cmd->cmd[i])
	{
		if (!check_syntax(cmd, cmd->cmd[i], update))
			return (false);
		key = NULL;
		value = NULL;
		if (get_key_and_value(cmd->cmd[i], &key, &value))
			concatenate_var(cmd->env, key, value);
		else
			enter_var(cmd->env, key, value);
		i++;
	}
	clean_exit(update, cmd);
	return (true);
}
