/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:48:47 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/19 07:24:15 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Includes
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <stdbool.h>
# include <termios.h>
# include <signal.h>
# include "../new_libft/libft.h"
# include "../garbage_collector/bin_malloc.h"
# include "types.h"
# include "parser.h"

// List for redirections
typedef struct s_filelist
{
	char				*filename; // filename
	t_type				type; // type of redirection
	struct s_filelist	*next; // pointer to the next node
}	t_filelist;

// Info and access to the filelist
typedef struct s_file
{
	t_filelist	*head;
	t_filelist	*tail;
	int			size;
}	t_file;

// Command list
typedef struct s_commandlist
{
	char					**cmd; // Command option and args. or NULL
	t_type					type; // type of token
	t_env					*env; // env list
	t_file					*files; // pointer to the file data struct
	int						logic_flag; // logical operator flag
	struct s_commandlist	*next; //pointer to the next command
}	t_commandlist;

// Info and access to the commandlist
typedef struct s_command
{
	int				size; // size of commandlist
	t_commandlist	*head; // pointer to the first node in the commandlist
	t_commandlist	*tail; // pointer to the last node in the commandlist
}	t_command;

// Signal
void	install_signals(void);
void	main_sigint_handler(int signum);
void	heredoc_sigint_handler(int signum);
void	child_sigint_handler(int signum);

// Env data struct 
bool	init_env(t_env *en, char **env, char **argv, int arg);
void	free_env_list(t_env *envc);
char	*get_env(char *lexeme, t_env *env);
bool	add_env_var(t_env *env, char *key, char *value);

// Parser
void	init_commands(t_command *cmd);
int		parse_tokens(t_command *cmd, t_tokens *tokens, t_env *env);
void	join_cmd_and_args(t_command *cmd, t_toklist *tokens, t_env *env);
void	enter_filelist(t_command *cmd, t_toklist *tokens);
void	free_tokens_list(t_tokens *tokens);
/*
	Connection point between parsing and execution
	place to check for edge cases and conversion
	- possible update function for calling
		minishell and the env functions
	- helping function for transformation
	- exit with a flag to know when to clean
*/
int		execute_commands(t_command *cmds);
char	**generate_env(t_env *env);
void	clean_exit(int update, t_commandlist *cmd);
/*
	The main caller:
	recursive _ execution
	helper to check edge case
*/
int		rec_exec(t_command *cmds, int start, int *prev_in_out, pid_t last_pid);
void	check_for_flag(t_commandlist **current, t_commandlist **prev);
/*
	All of its not static helper functions
	before actually running the command
	(double check is for logic operators)
	and going to return the last exit
*/
void	looking_for_pipes(t_command *cmds, int start, int *new_in_out);
int		check_redirection(t_commandlist *command, int control);
int		double_check(t_command *cmds, int start, int run_or_not);
int		wait_for_last(t_commandlist *cmds, pid_t last_pid);
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
pid_t	run_parent(t_commandlist *cmd, int *redirect,
			int *prev_in_out, int *new_in_out);
int		set_input(t_commandlist *cmd, int *redirect, int update);
int		handling_infile(t_commandlist *cmd, t_filelist	*current, int update);
int		handling_heredoc(t_commandlist *cmd, t_filelist	*current, int update);
int		set_output(t_commandlist *cmd, int *redirect, int update);
void	dup_and_or_close(int *prev_in_out, int *new_in_out);
char	*find_path(char *av, char **en);
/*
	Builtins main caller is a bulit in table
	the rest are non static fts being called
	and their helper functions that are related
*/
int		built_in_table(t_commandlist *cmd, char **env, int update);
void	ft_pwd(int update, t_commandlist *cmd);
void	ft_unset(t_commandlist *cmd, int update);
bool	ft_export(t_commandlist *cmd, int update);
void	report_export_syntax_error(t_commandlist *cmd, char *env, int update);
char	**find_key(t_env *env, char *key);
void	print_vars(t_commandlist *cmd, int update);
void	ft_env(char **env, int update, t_commandlist *cmd);
int		ft_exit(t_commandlist *cmd, int update);
void	should_we_print(int update);
/*
	Handling errors for different cases
	- general case
	- permission denied
	- directory of file not found
	- cd edge case
*/
int		standard_error(int update, t_commandlist *cmd);
int		path_error(t_commandlist *cmd, int update);
int		nofile_error(t_filelist *current, int update, t_commandlist *cmd);
int		nodir_error(t_commandlist *cmd, int update);
int		no_oldpwd(t_commandlist *cmd, int update, char *pwd);

#endif
