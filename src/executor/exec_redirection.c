#include "../../Includes/minishell.h"

/*
	Count all the inputs from file list
	so later we can get number of needed iterations
*/
static int	count_input(t_commandlist *cmd)
{
	int			inputs;
	t_filelist	*current;

	inputs = 0;
	current = cmd->files->head;
	while (current != NULL)
	{
		if (current->type == INFILE || current->type == HEREDOC)
			inputs++;
		current = current->next;
	}
	return (inputs);
}

/*
	as for infiles we have to go to the last one
	check for all of them if they are correct
	if not stop right here and don't execute
*/
static int	setting_input_file(t_commandlist *cmd)
{
	int			inputs;
	int			last;
	int			lc;
	t_filelist	*current;

	lc = 0;
	last = 0;
	inputs = count_input(cmd);
	if (inputs == 0)
		return (NO_REDIRECTION);
	current = cmd->files->head;
	while (current != NULL)
	{
		if (current->type == INFILE || current->type == HEREDOC)
		{
			last++;
			if (inputs == last)
				break ;
		}
		lc++;
		current = current->next;
	}
	return (lc);
}

/*
	Count all the outputs from file list
	same purpose as the one above for input
*/
static int	count_output(t_commandlist *cmd)
{
	int			outputs;
	t_filelist	*current;

	outputs = 0;
	current = cmd->files->head;
	while (current != NULL)
	{
		if (current->type == OUTFILE || current->type == APPEND)
			outputs++;
		current = current->next;
	}
	return (outputs);
}

/*
	setting the correct output used in run_cmd
*/
static int	setting_output_file(t_commandlist *cmd)
{
	int			outputs;
	int			lc;
	int			last;
	t_filelist	*current;

	lc = 0;
	last = 0;
	outputs = count_output(cmd);
	if (outputs == 0)
		return (NO_REDIRECTION);
	current = cmd->files->head;
	while (current != NULL)
	{
		if (current->type == OUTFILE || current->type == APPEND)
		{
			last++;
			if (outputs == last)
				break ;
		}
		lc++;
		current = current->next;
	}
	return (lc);
}

/*
	Check redirections in the parameter
	if there is one setting intput, output or both
*/
int	check_redirection(t_commandlist *command, int control)
{
	if (control == 0)
		return (setting_input_file(command));
	else if (control == 1)
		return (setting_output_file(command));
	return (NO_REDIRECTION);
}
