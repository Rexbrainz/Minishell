/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run_utility.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:20 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/14 10:35:53 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

/*
	per name
*/
int	handling_infile(t_commandlist *cmd, t_filelist	*current, int update)
{
	int	fd;

	fd = open(current->filename, O_RDONLY);
	if (fd == -1)
		return (nofile_error(current, update, cmd));
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), standard_error(update, cmd));
	return (close(fd), EXIT_SUCCESS);
}

/*
	once again per name:
	here doc is special case
	we don't create a file
	we save the input in name
*/
int	handling_heredoc(t_commandlist *cmd, t_filelist	*current, int update)
{
	int	heredoc_pipe[2];

	pipe(heredoc_pipe);
	if (current->filename != NULL && (*current->filename))
		ft_putstr_fd(current->filename, heredoc_pipe[1]);
	ft_putstr_fd("\n", heredoc_pipe[1]);
	close(heredoc_pipe[1]);
	if (dup2(heredoc_pipe[0], STDIN_FILENO) == -1)
		return (close(heredoc_pipe[0]), standard_error(update, cmd));
	close(heredoc_pipe[0]);
	return (EXIT_SUCCESS);
}

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
	fd = 0;
	current = cmd->files->head;
	while (lc < redirect[0])
	{
		if (current->type == INFILE)
		{
			fd = open(current->filename, O_RDONLY);
			if (fd == -1)
				return (nofile_error(current, update, cmd));
			close(fd);
		}
		lc++;
		current = current->next;
	}
	if (current->type == INFILE)
		return (handling_infile(cmd, current, update));
	else if (current->type == HEREDOC)
		return (handling_heredoc(cmd, current, update));
	return (EXIT_SUCCESS);
}

/*
	norminette fix, both cases in one helper function
*/
static int	helper_output(t_filelist *current, int update,
	int fd, t_commandlist *cmd)
{
	if (current->type == OUTFILE)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (current->type == APPEND)
		fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (nofile_error(current, update, cmd));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), standard_error(update, cmd));
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
		if (current->type == OUTFILE)
		{
			fd = open(current->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			close(fd);
		}
		else if (current->type == APPEND)
		{
			fd = open(current->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			close(fd);
		}
		lc++;
		current = current->next;
	}
	return (helper_output(current, update, fd, cmd));
}
