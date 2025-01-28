#include "minishell.h"

/*
	Looking for pipes and logic operators in context
	to know how many times we need to go to the next
*/
static int	find_leftmost(t_command *cmds, int start)
{
	int				cpo;
	int				end;
	t_commandlist	*current;

	cpo = 0;
	end = 0;
	current = cmds->head;
	while (current != NULL && current->next != NULL && cpo < start)	
	{
		if (current->type == AND || current->type == OR
			|| current->type == PIPE)
		{
			cpo++;
			if (cpo == start - 1)
				break ;
		}
		end++;
		current = current->next;
	}
	return (end);
}

/*
	Ensuring that you can keep going depending on logic operators
	looking at the exit of the last executed function to compare
*/
static int	keep_going(t_command *cmds, int last_exit, int end)
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
	if (current->type == AND && last_exit != 0)
		return (AND);
	else if (current->type == OR && last_exit == 0)
		return (OR);
	return (0);
}

/*
	Checking for redirections and if it should be executed
	we are also moving to command thats going to be executed
	when all above went okay we are calling the executor
*/
static int	check_execute(t_command *cmds, int start, int *prev_in_out, int *new_in_out)
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
		Possible recursive execution
	- finding left most with highest priority (after PIPE/AND/OR)
	- saving the exit code to the next part of (left most +1)
	- divided by two because we increment start + 2 and
	for each OR / AND / PIPE we have to call execve + 1 times
	- returning the last exit code and wait for proccesses
*/
int	rec_exec(t_command *cmds, int start, int *prev_in_out)
{
	int	last_exit;
	int	new_in_out[2];
	int	run_or_not;

	last_exit = 0;
	new_in_out[0] = NO_REDIRECTION;
	new_in_out[1] = NO_REDIRECTION;
	looking_for_pipes(cmds, start, new_in_out);
	run_or_not = keep_going(cmds, last_exit, find_leftmost(cmds, start));
	if (run_or_not != 0)
	{
		if (prev_in_out[0] != NO_REDIRECTION)
			close(prev_in_out[0]);
		start = double_check(cmds, start, run_or_not);
		if (start == 0)
			return (waiting_for_everyone(), last_exit);
		rec_exec(cmds, start, new_in_out);
	}
	else
		last_exit = check_execute(cmds, start, prev_in_out, new_in_out);
	if ((start / 2) < c_pipes_operators(cmds))
		rec_exec(cmds, start + 2, new_in_out);
	if (prev_in_out[0] != NO_REDIRECTION)
		close(prev_in_out[0]);
	return (waiting_for_everyone(), last_exit);
}
