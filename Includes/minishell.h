#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

// Infile <, Outfile >, Append >>, Heredoc <<.
typedef enum e_types
{
	WORD,
	BUILTIN,
	PIPE,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC
}	t_types;

typedef struct s_filelist
{
	char				*filename;
	int					type;
	struct s_filelist	*next;
}	t_filelist;

typedef struct s_file
{
	t_filelist	*head;
	t_filelist	*tail;
	int			size;
}	t_file;

typedef struct s_commandlist
{
	char					**cmd;
	int						type;
	t_file					*files;
	struct s_commandlist	*next;
}	t_commandlist;

typedef struct s_command
{
	t_command	*head;
	t_command	*tail;
	int			size;
}	t_command;

#endif
