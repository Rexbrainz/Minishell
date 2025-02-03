#include "minishell.h"

/*
	Flag if its a child process
	if so we need to clean memory
*/
void	clean_exit(int update)
{
	if (update == NO_REDIRECTION)
	{
		bin_malloc(-1);
		exit(EXIT_SUCCESS);
	}
}

/*
	TBD: check if it works correctly
	with all the redirections etc.
	(seems to be working)
*/
static void	ft_env(char **env, int update)
{
	int	cc;

	cc = 0;
	while (env[cc] != NULL)
	{
		ft_putstr_fd(env[cc], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		cc++;
	}
	clean_exit(update);
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
	clean_exit(update);
}

/*
	Look through and execute proper BUILTIN
*/
void	built_in_table(t_commandlist *cmd, char **env, int update)
{
	if (ft_strncmp("echo", cmd->cmd[0], 4) == 0)
		ft_echo(cmd, update);
	else if (ft_strncmp("cd", cmd->cmd[0], 2) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("pwd", cmd->cmd[0], 3) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("export", cmd->cmd[0], 6) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("unset", cmd->cmd[0], 5) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("env", cmd->cmd[0], 3) == 0)
		ft_env(env, update);
	else if (ft_strncmp("exit", cmd->cmd[0], 4) == 0)
	{
		if (update != NO_REDIRECTION)
			bin_malloc(-1);
		exit(EXIT_SUCCESS);
	}
}
