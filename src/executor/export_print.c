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
