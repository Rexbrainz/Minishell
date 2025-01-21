#include "minishell.h"

/*
	env command just as a DUMMY function
*/
static void	ft_env(char **env)
{
	int	cc;

	cc = 0;
	while (env[cc] != NULL)
	{
		ft_putstr_fd(env[cc], 1);
		cc++;
	}
}

/*
	Look through and execute proper BUILTIN
*/
void	built_in_table(t_commandlist *cmd, char **env)
{
	if (ft_strncmp("echo", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("cd", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("pwd", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("export", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("unset", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
	else if (ft_strncmp("env", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		ft_env(env);
	else if (ft_strncmp("exit", cmd->cmd[0], ft_strlen(cmd->cmd[0])) == 0)
		printf("Executing built-in: %s\n", cmd->cmd[0]);
}
