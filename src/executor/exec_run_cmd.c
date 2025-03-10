/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:52:51 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/17 14:15:26 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*
	Table to handle the pipes, duplication and/or closing:
	- we read input from the previous one (prev[0] reading)
	- if new pipe was created we connect it ([1] writing)
	- closing everything after the usage in child proc
*/
void	dup_and_or_close(int *prev_in_out, int *new_in_out)
{
	if (prev_in_out[0] != NO_REDIRECTION)
	{
		dup2(prev_in_out[0], STDIN_FILENO);
		close(prev_in_out[0]);
		prev_in_out[0] = NO_REDIRECTION;
	}
	if (new_in_out[1] != NO_REDIRECTION)
	{
		dup2(new_in_out[1], STDOUT_FILENO);
		close(new_in_out[1]);
		new_in_out[1] = NO_REDIRECTION;
	}
	if (prev_in_out[1] != NO_REDIRECTION)
	{
		close(prev_in_out[1]);
		prev_in_out[1] = NO_REDIRECTION;
	}
	if (new_in_out[0] != NO_REDIRECTION)
	{
		close(new_in_out[0]);
		new_in_out[0] = NO_REDIRECTION;
	}
}

/*
		we keep information what to open / create from redirect
	redirect input from the pipe before and write from the one going
*/
static void	set_input_output(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	if (redirect[0] != NO_REDIRECTION)
	{
		set_input(cmd, redirect, NO_REDIRECTION);
		prev_in_out[0] = NO_REDIRECTION;
		new_in_out[0] = NO_REDIRECTION;
	}
	if (redirect[1] != NO_REDIRECTION)
	{
		set_output(cmd, redirect, NO_REDIRECTION);
		new_in_out[1] = NO_REDIRECTION;
	}
}

/*
	Running the child process and setting up the redirection
	making a choice between builtin or normal command
*/
static int	child_proc(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	char	*path;
	char	**env;

	set_input_output(cmd, redirect, prev_in_out, new_in_out);
	dup_and_or_close(prev_in_out, new_in_out);
	env = generate_env(cmd->env);
	if (cmd->type == BUILTIN)
		built_in_table(cmd, env, NO_REDIRECTION);
	if (cmd->type == DOLLAR)
	{
		if (ft_strchr(cmd->cmd[0], ' ') != NULL)
			cmd->cmd = bin_split(cmd->cmd[0], ' ');
	}
	if (ft_strchr(cmd->cmd[0], '/') != NULL)
		path = bin_strdup(cmd->cmd[0]);
	else
	{
		path = find_path(cmd->cmd[0], env);
		if (path == NULL)
			path_error(cmd, NO_REDIRECTION);
	}
	if (execve(path, cmd->cmd, env) < 0)
		path_error(cmd, NO_REDIRECTION);
	return (EXIT_FAILURE);
}

/*
	safety measures not to double close
	closing whats not needed in the parent
*/
static void	close_and_reset(int *prev_in_out, int *new_in_out, int *reset)
{
	if (prev_in_out[0] != NO_REDIRECTION)
	{
		close(prev_in_out[0]);
		prev_in_out[0] = NO_REDIRECTION;
	}
	if (new_in_out[1] != NO_REDIRECTION)
	{
		close(new_in_out[1]);
		new_in_out[1] = NO_REDIRECTION;
	}
	dup2(reset[0], STDIN_FILENO);
	dup2(reset[1], STDOUT_FILENO);
	close(reset[0]);
	close(reset[1]);
}

/*
		Execution one per command
	depending on the flag with or without forking
*/
pid_t	run_cmd(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	pid_t	child;
	int		reset[2];

	reset[0] = dup(STDIN_FILENO);
	reset[1] = dup(STDOUT_FILENO);
	if (cmd != NULL && cmd->logic_flag == NO_REDIRECTION)
		child = run_parent(cmd, redirect, prev_in_out, new_in_out);
	else
	{
		child = fork();
		if (child == -1)
			standard_error(0, cmd);
		signal(SIGINT, SIG_IGN);
		if (child == 0)
		{
			signal(SIGINT, child_sigint_handler);
			if (child_proc(cmd, redirect, prev_in_out, new_in_out) < 0)
				standard_error(NO_REDIRECTION, cmd);
		}
	}
	close_and_reset(prev_in_out, new_in_out, reset);
	return (child);
}
