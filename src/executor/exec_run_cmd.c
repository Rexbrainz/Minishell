#include "minishell.h"

/*
	Close the pipe in and out
	output to STDERR the error
*/
static void	close_and_error(int *pipe_in_out)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	close(pipe_in_out[0]);
	close(pipe_in_out[1]);
	exit(errno);
}

/*
	if we found that there was an input redirect
	we are setting it up to be used by proccess
*/
static void	set_input(t_commandlist *cmd, int *pipe_in_out, int *redirect)
{
	int			fd;
	int			lc;
	t_filelist	*current;

	lc = 0;
	current = cmd->files->head;
	while (lc < redirect[0])
	{
		lc++;
		current = current->next;
	}
	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
		close_and_error(pipe_in_out);
	if (dup2(pipe_in_out[1], STDOUT_FILENO) == -1)
		close_and_error(pipe_in_out);
	if (dup2(fd, STDIN_FILENO) == -1)
		close_and_error(pipe_in_out);
}

/*
	just like above but for the outpu
*/
static void	set_output(t_commandlist *cmd, int *pipe_in_out, int *redirect)
{
	int			fd;
	int			lc;
	t_filelist	*current;

	lc = 0;
	current = cmd->files->head;
	while (lc < redirect[1])
	{
		lc++;
		current = current->next;
	}
	fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		close_and_error(pipe_in_out);
	if (dup2(pipe_in_out[0], STDIN_FILENO) == -1)
		close_and_error(pipe_in_out);
	if (dup2(fd, STDOUT_FILENO) == -1)
		close_and_error(pipe_in_out);
}

/*
	Running the child process and setting up the redirection
	we keep information what to open / create from redirect
	making a choice between builtin or normal command
*/
static int	child_proc(t_commandlist *cmd, char **env, int *pipe_in_out, int *redirect)
{
	char	*path;

	if (redirect[0] != -1)
		set_input(cmd, pipe_in_out, redirect);
	if (redirect[1] != -1)
		set_output(cmd, pipe_in_out, redirect);
	if (cmd->type == BUILTIN)
		built_in_table(cmd, env);
	path = find_path(cmd->cmd[0], en);
	if (path == NULL)
		close_and_error(pip_in_out);
	execve(path, cmd->cmd, env);
	return (EXIT_FAILURE)
}

/*
	Reworked pipex to run single command
	return status to check if we keep going
*/
int	run_cmd(t_commandlist *cmd, char **env, int *redirect)
{
	int		pipe_in_out[2];
	pid_t	child;
	int		status;

	pipe(pipe_in_out);
	child = fork();
	if (child == -1)
		close_and_error(pipe_in_out);
	else if (child == 0)
		if (child_proc(cmd, env, pip_in_out) < 0)
			close_and_error(pipe_in_out);
	close(pipe_in_out[0]);
	close(pipe_in_out[1]);
	waitpid(child, &status, 0);
	if (WIFEXITED(status) == 0)
		return (WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}
