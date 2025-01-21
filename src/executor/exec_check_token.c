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
static int	run_one(t_commandlist *one, char **env)
{
	// int				redirect[2];

	// redirect[0] = -1;
	// redirect[1] = -1;
	// if (one->files != NULL)
	// {
	// 	redirect[0] = check_redirection(one, 0);
	// 	redirect[1] = check_redirection(one, 1);
	// }
	built_in_table(one, env);
	return (EXIT_SUCCESS);
}

/*
	Taking the information from parser:
	- running checks for special case
	- going to actual execution
	TBD:
	- the process stopped because of logic operator,
	but it should be going to start from another place
	- creating a wait overhere not in execution,
	as of right now it isn't asynchronus
	- PIPES ARE NOT WORKING EEEEEE
*/
int	run_tokens(t_command *cmds, char **env)
{
	t_commandlist	*current;
	int				exit_code;

	current = cmds->head;
	exit_code = 0;
	if (lonely_builtin(cmds) == 0)
		exit_code = run_one(current, env);
	exit_code = rec_exec(cmds, env, 0);
	return (exit_code);
}
