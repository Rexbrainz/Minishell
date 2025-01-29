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
	int				redirect[2];

	redirect[0] = NO_REDIRECTION;
	redirect[1] = NO_REDIRECTION;
	if (one->files != NULL)
	{
		redirect[0] = check_redirection(one, 0);
		redirect[1] = check_redirection(one, 1);
	}
	if (redirect[0] != NO_REDIRECTION)
		set_input(one, redirect);
	if (redirect[1] != NO_REDIRECTION)
		set_output(one, redirect);
	built_in_table(one, env, 1);
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
*/
int	run_tokens(t_command *cmds)
{
	t_commandlist	*current;
	int				starting_in_out[2];
	int				exit_code;

	current = cmds->head;
	starting_in_out[0] = NO_REDIRECTION;
	starting_in_out[1] = NO_REDIRECTION;
	exit_code = 0;
	if (lonely_builtin(cmds) == 0)
		exit_code = run_one(current, current->env);
	exit_code = rec_exec(cmds, 0, starting_in_out);
	return (exit_code);
}
