/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:16 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 14:53:17 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*
	Helper function to keep track of input/output
	checking if there was an error to be worried
*/
static int	setting_in_out(t_commandlist *one, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	int	possible_error;

	possible_error = 0;
	if (redirect[0] != NO_REDIRECTION)
	{
		possible_error = set_input(one, redirect, 0);
		prev_in_out[0] = NO_REDIRECTION;
		new_in_out[0] = NO_REDIRECTION;
		if (possible_error != EXIT_SUCCESS)
			return (possible_error);
	}
	if (redirect[1] != NO_REDIRECTION)
	{
		possible_error = set_output(one, redirect, 0);
		new_in_out[1] = NO_REDIRECTION;
		if (possible_error != EXIT_SUCCESS)
			return (possible_error);
	}
	return (possible_error);
}

/*
	Special case only if both are true:
	- command is a BUILTIN
	- comes before or after logic operator
*/
pid_t	run_parent(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	int		possible_error;

	possible_error = setting_in_out(cmd, redirect, prev_in_out, new_in_out);
	dup_and_or_close(prev_in_out, new_in_out);
	if (possible_error != EXIT_SUCCESS)
		return (cmd->env->pid);
	possible_error = built_in_table(cmd, generate_env(cmd->env), 1);
	return (cmd->env->pid);
}
