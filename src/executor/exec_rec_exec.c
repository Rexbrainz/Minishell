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
		return (1);
	else if (current->type == OR && last_exit == 0)
		return (1);
	return (0);
}

/*
	Checking for redirections and if it should be executed
	if not we gonna stop at once and return the errors
	we are also moving to command thats going to be executed
	when all above went okay we are calling the executor
*/
static int	check_execute(t_command *cmds, int start, int *pipe_in_out)
{
	int				redirect[2];
	int				find_start;
	t_commandlist	*current;

	find_start = 0;
	current = cmds->head;
	redirect[0] = NO_REDIRECTION;
	redirect[1] = NO_REDIRECTION;
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
	return (run_cmd(current, cmds->env, redirect, pipe_in_out));
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
	- returning the last exit code
	- divided by two because we increment start + 2 and
	for each OR / AND / PIPE we have to call execve + 1 times
*/
int	rec_exec(t_command *cmds, int start)
{
	int	last_exit;
	int	pipe_in_out[2];

	last_exit = 0;
	looking_for_pipes(cmds->head, start, pipe_in_out);
	if (keep_going(cmds, last_exit, find_leftmost(cmds, start)) != 0)
		return (last_exit);
	last_exit = check_execute(cmds, start, pipe_in_out);
	if ((start / 2) < c_pipes_operators(cmds))
		rec_exec(cmds, start + 2);
	return (last_exit);
}
