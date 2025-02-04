#include "../../Includes/minishell.h"

/*
	if we found that there was an input redirect
	we are setting it up to be used by proccess
*/
int	set_input(t_commandlist *cmd, int *redirect, int update)
{
	int			fd;
	int			lc;
	t_filelist	*current;

	lc = 0;
	current = cmd->files->head;
	while (lc < redirect[0])
	{
		if (current->type == INFILE)
		{
			fd = open(current->filename, O_RDONLY);
			if (fd == -1)
				return (nofile_error(current, update));
		}
		lc++;
		current = current->next;
	}
	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
		return (nofile_error(current, update));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (standard_error(update));
	close(fd);
	return (EXIT_SUCCESS);
}

/*
	just like above but for the output
*/
int	set_output(t_commandlist *cmd, int *redirect, int update)
{
	int			fd;
	int			lc;
	t_filelist	*current;

	lc = 0;
	fd = 0;
	current = cmd->files->head;
	while (lc < redirect[1])
	{
		lc++;
		current = current->next;
	}
	if (current->type == OUTFILE)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == APPEND)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (nofile_error(current, update));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (standard_error(update));
	close(fd);
	return (EXIT_SUCCESS);
}

/*
	Table to handle the pipes, duplication and/or closing:
	- we read input from the previous one (prev[0] reading)
	- if new pipe was created we connect it ([1] writing)
	- closing everything after the usage in child proc
*/
static void	dup_and_or_close(int *prev_in_out, int *new_in_out)
{
	if (prev_in_out[0] != NO_REDIRECTION)
	{
		dup2(prev_in_out[0], STDIN_FILENO);
		close(prev_in_out[0]);
	}
	if (new_in_out[1] != NO_REDIRECTION)
	{
		dup2(new_in_out[1], STDOUT_FILENO);
		close(new_in_out[1]);
	}
	if (prev_in_out[0] != NO_REDIRECTION)
		close(prev_in_out[0]);
	if (prev_in_out[1] != NO_REDIRECTION)
		close(prev_in_out[1]);
	if (new_in_out[0] != NO_REDIRECTION)
		close(new_in_out[0]);
	if (new_in_out[1] != NO_REDIRECTION)
		close(new_in_out[1]);
}

/*
	Running the child process and setting up the redirection
	we keep information what to open / create from redirect
	making a choice between builtin or normal command
	redirect input from the pipe before and write from the one going
*/
static int	child_proc(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	char	*path;

	if (redirect[0] != NO_REDIRECTION)
		set_input(cmd, redirect, NO_REDIRECTION);
	if (redirect[1] != NO_REDIRECTION)
		set_output(cmd, redirect, NO_REDIRECTION);
	dup_and_or_close(prev_in_out, new_in_out);
	if (cmd->type == BUILTIN)
		built_in_table(cmd, cmd->env, NO_REDIRECTION);
	path = find_path(cmd->cmd[0], cmd->env);
	if (path == NULL)
		path_error(cmd, NO_REDIRECTION);
	if (execve(path, cmd->cmd, cmd->env) < 0)
		standard_error(NO_REDIRECTION);
	return (EXIT_FAILURE);
}

/*
	Reworked pipex to run single command
	return status to check if we keep going
*/
pid_t	run_cmd(t_commandlist *cmd, int *redirect,
	int *prev_in_out, int *new_in_out)
{
	pid_t	child;

	child = fork();
	if (child == -1)
		standard_error(0);
	else if (child == 0)
	{
		if (child_proc(cmd, redirect, prev_in_out, new_in_out) < 0)
			standard_error(NO_REDIRECTION);
	}
	if (prev_in_out[0] != NO_REDIRECTION)
		close(prev_in_out[0]);
	if (new_in_out[1] != NO_REDIRECTION)
		close(new_in_out[1]);
	return (child);
}
