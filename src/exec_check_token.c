#include "minishell.h"

int	check_for_file(t_file *files)
{
	t_filelist	*current;
	int			fd;

	if (files->size <= 0)
		return (0);
	current = files->head;
	while (current != NULL)
	{
		if (current->type == INFILE)
		{
			fd = open(current->filename, O_RDONLY);
			if (fd == -1)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(current->filename, 2);
				ft_putstr_fd(": No such file or directory", 2);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int	lonely_builtin(t_command *cmds)
{
	if (cmds->size != 1)
		return (1);
	if (cmds->head->type != BUILTIN)
		return (1);
	return (0);
}
