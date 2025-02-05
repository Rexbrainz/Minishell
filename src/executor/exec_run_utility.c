#include "../../Includes/minishell.h"

int	handling_infile(t_filelist	*current, int update)
{
	int	fd;

	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
		return (nofile_error(current, update));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), standard_error(update));
	return (close(fd), EXIT_SUCCESS);
}

int	handling_heredoc(t_filelist	*current, int update)
{
	int	heredoc_pipe[2];

	pipe(heredoc_pipe);
	if (current->filename != NULL && (*current->filename))
		ft_putstr_fd(current->filename, heredoc_pipe[1]);
	ft_putstr_fd("\n", heredoc_pipe[1]);
	close(heredoc_pipe[1]);
	if (dup2(heredoc_pipe[0], STDIN_FILENO) == -1)
		return (close(heredoc_pipe[0]), standard_error(update));
	close(heredoc_pipe[0]);
	return (EXIT_SUCCESS);
}
