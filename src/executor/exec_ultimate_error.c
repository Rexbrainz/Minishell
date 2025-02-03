#include "../../Includes/minishell.h"

/*
	General error message after checks
	- if no extra work is needed
*/
void	standard_error(int update)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		bin_malloc(-1);
		exit(errno);
	}
}

/*
	Command not found because my errno was wrong
	- displayed after the path failed
*/
void	path_error(t_commandlist *cmd, int update)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->cmd[0], STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		bin_malloc(-1);
		exit(127);
	}
}

/*
	No file with extra informations
	- because standard doesn't show which one
		is missing from the files / directories
*/
void	nofile_error(t_filelist *current, int update)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(current->filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	if (update == NO_REDIRECTION)
	{
		bin_malloc(-1);
		exit(errno);
	}
}
