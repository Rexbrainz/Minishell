#include "../../Includes/minishell.h"

/*
	check if we need to create another pipe
*/
void	looking_for_pipes(t_command *cmds, int start, int *new_in_out)
{
	int				find_start;
	t_commandlist	*current;

	find_start = 0;
	current = cmds->head;
	while (find_start < start && current != NULL)
	{
		find_start++;
		current = current->next;
	}
	if (current != NULL && current->next != NULL)
	{
		if (current->next->type == PIPE)
			pipe(new_in_out);
	}
}

/*
	capturing the last exit command
	and waiting for the rest
*/
int	wait_for_last(t_commandlist *cmd, pid_t last_pid)
{
	int		status;
	int		saving;
	pid_t	waiting_for_each;

	status = 0;
	saving = 0;
	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		saving = WEXITSTATUS(status);
	while (errno != ECHILD)
	{
		waiting_for_each = waitpid(-1, &status, 0);
		if (waiting_for_each == -1)
		{
			if (errno == ECHILD)
				break ;
			else
				standard_error(NO_REDIRECTION, cmd);
		}
	}
	signal(SIGINT, main_sigint_handler);
	return (saving);
}

/*
	Finding the next opposite sign as start
	for OR its AND and the other way around
*/
static int	find_opposite(t_commandlist *current,
	int find_start, int run_or_not)
{
	if (run_or_not == AND)
	{
		while (current != NULL)
		{
			if (current->type == OR)
				return (find_start + 1);
			find_start++;
			current = current->next;
		}
	}
	else if (run_or_not == OR)
	{
		while (current != NULL)
		{
			if (current->type == AND)
				return (find_start + 1);
			find_start++;
			current = current->next;
		}
	}
	return (0);
}

/*
	Making sure that the execution should end
	for the case of cmd1 || cmd2 && cmd3
	we should execute first one and last
	and in the case of cmd1 && cmd2 || cmd3
	if first fails we should execute the last
*/
int	double_check(t_command *cmds, int start, int run_or_not)
{
	int				find_start;
	t_commandlist	*current;

	find_start = 0;
	current = cmds->head;
	while (find_start < start && current != NULL)
	{
		find_start++;
		current = current->next;
	}
	return (find_opposite(current, find_start, run_or_not));
}

/*
		extra case for the case  of $EXPAND_TO_NOTHING
	in that case if its not the executable we move it to next
		setting a flag if we should execute in parent
	case for builtin before or after the logic operator
*/
void	check_for_flag(t_commandlist **current, t_commandlist **prev)
{
	if ((*current) != NULL && (*current)->next != NULL
		&& ((*current)->type == PIPE || (*current)->type == AND
			|| (*current)->type == OR))
		(*current) = (*current)->next;
	if ((*current) != NULL && (*current)->type == BUILTIN)
	{
		if ((*current)->next != NULL && (*current)->next->type != PIPE)
			(*current)->logic_flag = NO_REDIRECTION;
		else if ((*prev) != NULL && (*prev)->type != PIPE)
		{
			if (ft_strcmp("exit", (*current)->cmd[0]) == 0)
				(*current)->logic_flag = NO_REDIRECTION;
			else
				(*current)->logic_flag = 0;
		}
	}
}
