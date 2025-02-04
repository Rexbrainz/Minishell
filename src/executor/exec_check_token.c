#include "../../Includes/minishell.h"

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
	Helper function to keep track of input/output
	saving them if needed to be later on restored
*/
static int	saving_in_out(t_commandlist *one, int *redirect, int *reset)
{
	int	possible_error;

	possible_error = 0;
	if (redirect[0] != NO_REDIRECTION)
	{
		reset[0] = dup(STDIN_FILENO);
		possible_error = set_input(one, redirect, 0);
		if (possible_error != EXIT_SUCCESS)
			return (possible_error);
	}
	if (redirect[1] != NO_REDIRECTION)
	{
		reset[1] = dup(STDOUT_FILENO);
		possible_error = set_output(one, redirect, 0);
		if (possible_error != EXIT_SUCCESS)
			return (possible_error);
	}
	return (possible_error);
}

/*
	per name function
*/
static void	restoring_in_out(int *reset)
{
	if (reset[0] != NO_REDIRECTION)
	{
		dup2(reset[0], STDIN_FILENO);
		close (reset[0]);
	}
	if (reset[1] != NO_REDIRECTION)
	{
		dup2(reset[1], STDOUT_FILENO);
		close (reset[1]);
	}
}

/*
	Executing the edge case the only command is BUILTIN
	we need to add the case if there was an error
	to stop the rest of the execution without exiting
*/
static int	run_one(t_commandlist *one, char **env)
{
	int	redirect[2];
	int	reset[2];
	int	possible_error;

	redirect[0] = NO_REDIRECTION;
	redirect[1] = NO_REDIRECTION;
	reset[0] = NO_REDIRECTION;
	reset[1] = NO_REDIRECTION;
	possible_error = 0;
	if (one->files != NULL)
	{
		redirect[0] = check_redirection(one, 0);
		redirect[1] = check_redirection(one, 1);
	}
	possible_error = saving_in_out(one, redirect, reset);
	if (possible_error != EXIT_SUCCESS)
		return (restoring_in_out(reset), possible_error);
	built_in_table(one, env, 1);
	restoring_in_out(reset);
	return (EXIT_SUCCESS);
}

/*
	Taking the information from parser:
	- running checks for special case
	- going to actual execution
*/
int	execute_commands(t_command *cmds)
{
	t_commandlist	*current;
	int				starting_in_out[2];
	int				exit_status;

	current = cmds->head;
	exit_status = 0;
	starting_in_out[0] = NO_REDIRECTION;
	starting_in_out[1] = NO_REDIRECTION;
	if (lonely_builtin(cmds) == 0)
		exit_status = run_one(current, current->env);
	else
		exit_status = rec_exec(cmds, 0, starting_in_out, 0);
	return (exit_status);
}
