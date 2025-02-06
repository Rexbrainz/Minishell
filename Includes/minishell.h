#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>
# include "../new_libft/libft.h"
# include "../garbage_collector/bin_malloc.h"

// Infile <, Outfile >, Append >>, Heredoc <<.
typedef enum e_types
{
	NO_REDIRECTION = -1,
	WORD,
	BUILTIN,
	PIPE,
	AND,
	OR,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
	OPTIONS,
	DOLLAR,
	S_QUOTE,
	D_QUOTE,
	LEFT_PAREN,
	RIGHT_PAREN,
	STAR,
	CMD_SUB,
	EXIT_STAT,
	BACK_SLASH,
	NOTHING
}	t_type;

# include "../src/parser/parser.h"
/*
typedef struct s_envlist
{
	
}
*/
typedef struct s_filelist
{
	char				*filename;
	t_type				type;
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
	t_type					type;
	t_file					*files;
	char					**env;
	struct s_commandlist	*next;
}	t_commandlist;

typedef struct s_command
{
	t_commandlist	*head;
	t_commandlist	*tail;
	int				size;
}	t_command;

void	init_commands(t_command *cmd);
int		parse_tokens(t_command *cmd, t_tokens *tokens, char **env);
void	join_cmd_and_args(t_command *cmd, t_toklist *tokens, char **env);
bool	add_cmd(t_command *cmd, char **cmd_args, t_type type, t_file *file);
void	enter_filelist(t_command *cmd, t_toklist *tokens);
void	free_tokens_list(t_tokens *tokens);
void	free_cmds_list(t_command *cmd);
/*
	Connection point between parsing and execution
	place to check for edge cases and conversion
	- possible update function for calling
		minishell and the env functions
*/
int		execute_commands(t_command *cmds);
/*
	The main caller:
	recursive _ execution
*/
int		rec_exec(t_command *cmds, int start, int *prev_in_out, pid_t last_pid);
/*
	All of its not static helper functions
	before actually running the command
	(double check is for logic operators)
	and going to return the last exit
*/
void	looking_for_pipes(t_command *cmds, int start, int *new_in_out);
int		check_redirection(t_commandlist *command, int control);
int		double_check(t_command *cmds, int start, int run_or_not);
int		wait_for_last(pid_t last_pid);
/*
	Running the actual commands
	in the running _ commands
	Pipes in out (prev and new):
	[0] is for reading (our in)
	[1] is for writing (our out)
	the rest are helper functions
*/
pid_t	run_cmd(t_commandlist *cmd, int *redirect,
			int *prev_in_out, int *new_in_out);
int		set_input(t_commandlist *cmd, int *redirect, int update);
int		handling_infile(t_filelist	*current, int update);
int		handling_heredoc(t_filelist	*current, int update);
int		set_output(t_commandlist *cmd, int *redirect, int update);
char	*find_path(char *av, char **en);
/*
	Builtins main caller and fts being called
	clean exit with a flag to know when to exit
*/
void	built_in_table(t_commandlist *cmd, char **env, int update);
void	ft_pwd(int update);
void	clean_exit(int update);
/*
	Handling errors for different cases
	- general case
	- permission denied
	- directory of file not found
*/
int		standard_error(int update);
int		path_error(t_commandlist *cmd, int update);
int		nofile_error(t_filelist *current, int update);
int		nodir_error(t_commandlist *cmd, int update);

#endif
