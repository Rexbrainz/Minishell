#include "../../Includes/minishell.h"

/*
	No comment needed for that one
	TBD: change in linked list env
*/
static void	ft_env(char **env, int update, t_commandlist *cmd)
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
	Echo, with option for the flag
	skip all the -n -n and -nnn
	add space between arguments
	don't add after the last one
*/
static void	ft_echo(t_commandlist *cmd, int update)
{
	int	cc;
	int	no_new_line;
	int	after_nl;

	cc = 0;
	no_new_line = 0;
	after_nl = 0;
	while (cmd->cmd[cc] != NULL)
	{
		if (ft_strncmp("-n", cmd->cmd[cc], 2) == 0 && after_nl == 0)
			no_new_line++;
		else if (cc != 0)
		{
			ft_putstr_fd(cmd->cmd[cc], STDOUT_FILENO);
			if (cmd->cmd[cc + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			after_nl++;
		}
		cc++;
	}
	if (no_new_line == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	clean_exit(update, cmd);
}

/*
	Special case for minus handling both
		- if there is OLDPWD
		- if there is no OLDPWD
*/
static int	cd_minus_case(t_commandlist *cmd, int update)
{
	char	*found_value;

	found_value = get_env("OLDPWD", cmd->env);
	if (found_value == NULL)
		return (no_oldpwd(cmd, update));
	else
	{
		ft_putstr_fd(found_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		chdir(found_value);
		free(found_value);
		return (0);
	}
}

/*
	Thank you Stelio
	added handling for:
	- / ~ / [NULL]
	updating OLDPWD
*/
static int	ft_cd(t_commandlist *cmd, int update)
{
	if (cmd->cmd[1] != NULL)
	{
		if (ft_strncmp("~", cmd->cmd[1], ft_strlen(cmd->cmd[1]) == 0))
			return (chdir(getenv("HOME")), 0);
	}
	if (chdir(cmd->cmd[1]) != 0)
	{
		if (cmd->cmd[1] != NULL)
		{
			if (ft_strncmp("-", cmd->cmd[1], ft_strlen(cmd->cmd[1])) == 0)
				return (cd_minus_case(cmd, update));
			else
				return (nodir_error(cmd, update));
		}
		else
			chdir(getenv("HOME"));
	}
	clean_exit(update, cmd);
	return (0);
}

/*
	Look through and execute proper BUILTIN
	we care about return value in edge case
	only builtin and no other delimiters
*/
int	built_in_table(t_commandlist *cmd, char **env, int update)
{
	if (ft_strncmp("echo", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (ft_echo(cmd, update), 0);
	else if (ft_strncmp("cd", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (ft_cd(cmd, update));
	else if (ft_strncmp("pwd", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (ft_pwd(update, cmd), 0);
	else if (ft_strncmp("export", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (printf("Executing built-in: %s\n", cmd->cmd[0]), 0);
	else if (ft_strncmp("unset", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (ft_unset(cmd, update), 0);
	else if (ft_strncmp("minishell", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (printf("Executing built-in: %s\n", cmd->cmd[0]), 0);
	else if (ft_strncmp("env", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (ft_env(env, update, cmd), 0);
	else if (ft_strncmp("exit", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		return (clean_exit(NO_REDIRECTION, cmd), 0);
	else
		return (path_error(cmd, update));
}
