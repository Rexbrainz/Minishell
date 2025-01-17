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
	while (current != NULL || cpo != start + 1)
	{
		if (current->type == AND || current->type == OR
			|| current->type == PIPE)
			cpo++;
		end++;
		current = current->next;
	}
	return (end);
}

/*
	Checking for redirections and if it should be executed
	if not we gonna stop at once and return the errors
	we are also moving to command thats going to be executed
	when all above went okay we are calling the executor
*/
static int	check_execute(t_command *cmds, char **env, int start)
{
	int				redirect[2];
	int				find_start;
	t_commandlist	*current;

	pipe(pipe_in_out);
	find_start = 0;
	current = cmds->head;
	redirect[0] = -1;
	redirect[1] = -1;
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
	run_cmd(current, env, redirect);
	return (0);
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
	- finding left most with highest priority (PIPE/AND/OR)
	- saving the exit code to the next part of (left most +1)
	- returning the last exit code
*/
int	rec_exec(t_command *cmds, char **env, int start)
{
	int	last_exit;
	int	end;

	last_exit = 0;
	end = find_leftmost(cmds, start);
	last_exit = check_execute(cmds, env, start);
	if (start <= c_pipes_operators(cmds))
		rec_exec(cmds, env, start + 1);
	return (last_exit);
}
