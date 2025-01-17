#include "minishell.h"

/*
	Special case when we run without forking:
	check if its not true we using rec_exec
*/
static int	lonely_builtin(t_command *cmds)
{
	if (cmds->size != 1)
		return (1);
	if (cmds->head->type != BUILTIN)
		return (1);
	return (0);
}

/*
	Executing the edge case
	the only command is BUILTIN	
*/
static int	run_one(t_commandlist *one)
{
	int				redirect[2];

	redirect[0] = -1;
	redirect[1] = -1;
	if (one->files != NULL)
	{
		redirect[0] = check_redirection(current, 0);
		redirect[1] = check_redirection(current, 1);
	}
	return (EXIT_SUCCESS);
}

/*
	Taking the information from parser:
	- running checks for special case
	- going to actual execution
*/
int	run_tokens(t_command *cmds, char **env)
{
	t_commandlist	*current;

	current = cmds->head;
	if (lonely_builtin(cmds) == 0)
		run_one(current);
	else
		rec_exec(cmds, env, 0);
	return (EXIT_SUCCESS);
}
