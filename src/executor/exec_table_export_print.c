#include "../../Includes/minishell.h"

/*
	Helper function for export works correctly 
	(+ 1 is for equal sign stored in value)
*/
void	print_vars(t_commandlist *cmd, int update)
{
	t_envlist	*curr;

	curr = cmd->env->head;
	while (curr)
	{
		if (curr->value)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(curr->key, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(curr->value + 1, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(curr->key, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		curr = curr->next;
	}
	clean_exit(update, cmd);
}

char	**find_key(t_env *env, char *key)
{
	t_envlist	*curr;

	curr = env->head;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			return (&curr->value);
		}
		curr = curr->next;
	}
	return (NULL);
}

void	report_export_syntax_error(t_commandlist *cmd, char *env, int update)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(env, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		rl_clear_history();
		bin_malloc(-1);
		exit(1);
	}
}

/*
	No comment needed for that one
*/
void	ft_env(char **env, int update, t_commandlist *cmd)
{
	int	cc;

	cc = 0;
	while (env[cc] != NULL)
	{
		ft_putstr_fd(env[cc], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		cc++;
	}
	clean_exit(update, cmd);
}

/*
	We are adding over here a check for exit
	just when we should print the message
*/
void	should_we_print(int update)
{
	if (update != NO_REDIRECTION)
		ft_printf("exit\n");
}
