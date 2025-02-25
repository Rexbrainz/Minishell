/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:52:17 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 14:52:18 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
static int	run_one(t_commandlist *one)
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
	possible_error = built_in_table(one, generate_env(one->env), 1);
	restoring_in_out(reset);
	return (possible_error);
}

/*
	Taking the information from parser:
	- running checks for special case
	- going to actual execution
echo "hello world" | tr '[:lower:]' '[:upper:]' > out.txt && cat out.txt
	- check for the null and ommit it
	through the execution parts when it appers
*/
int	execute_commands(t_command *cmds)
{
	t_commandlist	*current;
	int				starting_in_out[2];
	int				error_or_not;

	current = cmds->head;
	error_or_not = 0;
	if (current != NULL)
		error_or_not = current->env->exit_status;
	starting_in_out[0] = NO_REDIRECTION;
	starting_in_out[1] = NO_REDIRECTION;
	if (lonely_builtin(cmds) == 0)
		error_or_not = run_one(current);
	else
		error_or_not = rec_exec(cmds, 0, starting_in_out, 0);
	if (current != NULL)
		current->env->exit_status = error_or_not;
	return (error_or_not);
}
