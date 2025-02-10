#include "../../Includes/minishell.h"

static void	enter_var(t_env *env, char *key, char *value)
{
	char		**existing_value;

	existing_value = &key;
	existing_value = find_key(env, key);
	if (!existing_value)
		add_env_var(env, key, value);
	else if (value)
		*existing_value = value;
}

/*
	the main problem seems to be here
	we are calling add_env_var
	but it doesn't seem to be needed
	we would just need to update the values
	RE:
		Not really, if the key does not already exist,
		the new key and value are exported.
*/
static void	concatenate_var(t_env *env, char *key, char *value)
{
	char		*temp;
	char		**existing_value;

	temp = key;
	key = ft_substr(temp, 0, ft_strlen(temp) - 1);
	free(temp);
	existing_value = &temp;
	existing_value = find_key(env, key);
	if (!existing_value)
		add_env_var(env, key, value);
	else if (!*existing_value && value)
		*existing_value = value;
	else
	{
		if (!value)
			return ;
		temp = *existing_value;
		*existing_value = ft_strjoin(temp, value + 1);
		free(temp);
		free(value);
	}
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
	if (ft_strchr(*key, '+'))
		return (true);
	return (false);
}

static bool	check_syntax(t_commandlist *cmd, char *var, int update)
{
	char	*temp;

	temp = var;
	if (*var != '_' && !ft_isalpha(*var))
	{
		report_export_syntax_error(cmd, temp, update);
		return (false);
	}
	var++;
	while (*var && *var != '=')
	{
		if (*var == '+' && *(var + 1) == '=')
		{
			var++;
			continue ;
		}
		else if (*var != '_' && !ft_isalnum(*var))
		{
			report_export_syntax_error(cmd, temp, update);
			return (false);
		}
		var++;
	}
	return (true);
}

/*
	Export
	- print vars function now works correctly
	- The main problem is probably in concatenate
	check for the case when there is space before
*/
bool	ft_export(t_commandlist *cmd, int update)
{
	int			i;
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
