#include "../../Includes/minishell.h"

/*
	Ensuring that you can keep going depending on logic operators
	looking at the exit of the last executed function to compare
*/
static int	keep_going(t_command *cmds, pid_t last_pid, int end, int *exit_code)
{
	t_commandlist	*current;
	int				co;

	current = cmds->head;
	co = 0;
	while (current != NULL && co < end)
	{
		co++;
		current = current->next;
	}
	if (current->type == AND)
	{
		(*exit_code) = wait_for_last(last_pid);
		if ((*exit_code) != 0)
			return (AND);
	}
	else if (current->type == OR)
	{
		(*exit_code) = wait_for_last(last_pid);
		if ((*exit_code) == 0)
			return (OR);
	}
	return (0);
}

/*
	Checking for redirections and if it should be executed
	we are also moving to command thats going to be executed
	when all above went okay we are calling the executor
*/
static int	check_execute(t_command *cmds, int start,
	int *prev_in_out, int *new_in_out)
{
	int				redirect[2];
	int				find_start;
	t_commandlist	*current;

	redirect[0] = NO_REDIRECTION;
	redirect[1] = NO_REDIRECTION;
	find_start = 0;
	current = cmds->head;
	while (find_start < start && current != NULL)
	{
		find_start++;
		current = current->next;
	}
	if (current->files != NULL)
	{
		redirect[0] = check_redirection(current, 0);
		redirect[1] = check_redirection(current, 1);
	}
	return (run_cmd(current, redirect, prev_in_out, new_in_out));
}

/*
	Counter for total number of logic operators and pipes
	check used later on if we need to keep going
*/
static int	c_pipes_operators(t_command *cmds)
{
	int				cpo;
	t_commandlist	*current;

	cpo = 0;
	current = cmds->head;
	while (current != NULL)
	{
		if (current->type == AND || current->type == OR
			|| current->type == PIPE)
			cpo++;
		current = current->next;
	}
	return (cpo);
}

/*
	short up the main function
*/
static void	close_prev(int *prev_in_out)
{
	if (prev_in_out[0] != NO_REDIRECTION)
		close(prev_in_out[0]);
}

/*	
		recursive _ execution
	- check is divided by two because we increment start + 2
		command(0) OPERATOR(1) command(2)
	- returning the last exit code and wait for all processes
		saving exit for the case when pid was already used
*/
int	rec_exec(t_command *cmds, int start, int *prev_in_out, pid_t last_pid)
{
	pid_t	current_pid;
	int		new_in_out[2];
	int		run_or_not;
	int		exit_code;

	current_pid = 0;
	exit_code = 0;
	new_in_out[0] = NO_REDIRECTION;
	new_in_out[1] = NO_REDIRECTION;
	looking_for_pipes(cmds, start, new_in_out);
	run_or_not = keep_going(cmds, last_pid, start - 1, &exit_code);
	if (run_or_not != 0)
	{
		close_prev(prev_in_out);
		start = double_check(cmds, start, run_or_not);
		if (start == 0)
			return (exit_code);
		return (rec_exec(cmds, start, new_in_out, last_pid));
	}
	else
		current_pid = check_execute(cmds, start, prev_in_out, new_in_out);
	if ((start / 2) < c_pipes_operators(cmds))
		return (rec_exec(cmds, start + 2, new_in_out, current_pid));
	return (close_prev(prev_in_out), wait_for_last(current_pid));
}
