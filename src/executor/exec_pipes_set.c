#include "minishell.h"

static int	set_pipe_output(int *pipe_in_out)
{
	if (dup2(pipe_in_out[1], STDOUT_FILENO) == -1)
		return (-1);
	close(pipe_in_out[1]);
	return (PIPE);
}

static int	set_pipe_input(int *pipe_in_out)
{
	if (dup2(pipe_in_out[0], STDIN_FILENO) == -1)
		return (-1);
	close(pipe_in_out[0]);
	return (0);
}

void	looking_for_pipes(t_commandlist	*current, int start, int *pipe_in_out)
{
	int				find_start;
	static int		pipe_was_used;

	find_start = 0;
	while (find_start < start && current != NULL)
	{
		find_start++;
		current = current->next;
	}
	if (current->next != NULL)
	{
		if (current->next->type == PIPE)
		{
			pipe(pipe_in_out);
			pipe_was_used = set_pipe_output(pipe_in_out);
		}
	}
	if (pipe_was_used == PIPE)
		pipe_was_used = set_pipe_input(pipe_in_out);
}
