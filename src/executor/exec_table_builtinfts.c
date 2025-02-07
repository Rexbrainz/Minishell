#include "../../Includes/minishell.h"

/*
	Flag if its a child process
	if so we need to clean memory
*/
void	clean_exit(int update, t_commandlist *cmd)
{
	if (update == NO_REDIRECTION)
	{
		free_env_list(cmd->env);
		rl_clear_history();
		bin_malloc(-1);
		exit(EXIT_SUCCESS);
	}
}

/*
	get current directory
*/
void	ft_pwd(int update, t_commandlist *cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd);
	}
	clean_exit(update, cmd);
}
