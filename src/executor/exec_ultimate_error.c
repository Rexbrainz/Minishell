#include "../../Includes/minishell.h"

/*
	General error message after checks
	- if no extra work is needed
*/
int	standard_error(int update, t_commandlist *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		bin_malloc(-1);
		exit(errno);
	}
	return (errno);
}

/*
	Command not found because my errno was wrong
	- displayed after the path function failed
*/
int	path_error(t_commandlist *cmd, int update)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		bin_malloc(-1);
		exit(127);
	}
	return (127);
}

/*
	No file with extra informations
	- because standard doesn't show which one
		is missing from the files / directories
*/
int	nofile_error(t_filelist *current, int update, t_commandlist *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(current->filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		bin_malloc(-1);
		exit(errno);
	}
	return (errno);
}

/*
	no _ directory was found
*/
int	nodir_error(t_commandlist *cmd, int update)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd[1], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		bin_malloc(-1);
		exit(errno);
	}
	return (errno);
}

/*
	OLDPWD is not set
*/
int	no_oldpwd(t_commandlist *cmd, int update, char *pwd)
{
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
	if (pwd != NULL)
	{
		free(pwd);
		pwd = NULL;
	}
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		bin_malloc(-1);
		exit(1);
	}
	return (1);
}
