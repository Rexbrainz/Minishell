#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../new_libft/libft.h"
# include "../src/parser/scanner.h"
//# include "../src/parser/parser.h"

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
	t_commandlist	*head;
	t_commandlist	*tail;
	int				size;
}	t_command;

void		init_commands(t_command *cmd);
t_tokens	*parse_line(t_command *cmd, t_tokens *tokens);
void		join_cmd_and_args(t_command *cmd, t_toklist *head);
bool		add_cmd(t_command *cmd, char **cmd_args, t_type type, t_file *file);

#endif
