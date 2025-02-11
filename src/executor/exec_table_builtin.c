#include "../../Includes/minishell.h"

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
	setting the OLDPWD
	Does't work for the case of just running
	cd it fails pointer being fread but not allocated
*/
static void	set_oldpwd(t_commandlist *info, char *pwd)
{
	t_commandlist	*oldpwd;

	oldpwd = bin_malloc(sizeof(t_commandlist));
	oldpwd->cmd = bin_malloc(sizeof(char *) * 3);
	oldpwd->cmd[0] = bin_strdup("export");
	oldpwd->cmd[1] = bin_strjoin("OLDPWD=", pwd);
	oldpwd->cmd[2] = NULL;
	oldpwd->env = info->env;
	if (pwd != NULL)
	{
		free(pwd);
		pwd = NULL;
	}
	ft_export(oldpwd, 1);
}

/*
	Special case for minus handling both
		- if there is OLDPWD
		- if there is no OLDPWD
*/
static int	cd_minus_case(t_commandlist *cmd, int update, char *pwd)
{
	char	*found_value;

	found_value = get_env("OLDPWD", cmd->env);
	if (found_value == NULL)
		return (clean_exit(update, cmd), no_oldpwd(cmd, update, pwd));
	else
	{
		set_oldpwd(cmd, pwd);
		ft_putstr_fd(found_value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		chdir(found_value);
		free(found_value);
		clean_exit(update, cmd);
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
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (cmd->cmd[1] == NULL)
		return (set_oldpwd(cmd, pwd), chdir(getenv("HOME")), clean_exit(update, cmd), 0);
	else if (chdir(cmd->cmd[1]) != 0)
	{
		if (cmd->cmd[1] != NULL)
		{
			if (ft_strncmp("-", cmd->cmd[1], ft_strlen(cmd->cmd[1])) == 0)
				return (cd_minus_case(cmd, update, pwd));
			else if (ft_strncmp("~", cmd->cmd[1], ft_strlen(cmd->cmd[1])) == 0)
				return (set_oldpwd(cmd, pwd), chdir(getenv("HOME")), clean_exit(update, cmd), 0);
			else
				return (free(pwd), pwd = NULL, nodir_error(cmd, update));
		}
	}
	else
		set_oldpwd(cmd, pwd);
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
	{
		if (ft_export(cmd, update) == false)
			return (1);
		else
			return (0);
	}
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
