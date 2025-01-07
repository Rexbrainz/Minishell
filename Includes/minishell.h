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
	struct s_file_node	*next;
}	t_filelist;

typedef struct s_file
{
	t_file_node	*head;
	t_file_node	*tail;
	int			size;
}	t_file;

typedef struct s_commandlist
{
	char			**cmd;
	int				type;
	t_file_list		*file_list;
	struct s_node	*next;
}	t_commandlist;

typedef struct s_command
{
	t_file_node	*head;
	t_file_node	*tail;
	int			size;
}	t_command;

#endif