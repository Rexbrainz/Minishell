#include "../../Includes/minishell.h"

void	ft_pwd(int update)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		free(pwd);
	}
	clean_exit(update);
}
