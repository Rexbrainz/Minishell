/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 11:02:21 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include <stdio.h>
//# include <unistd.h>
//# include <readline/readline.h>
//# include <readline/history.h>
//# include <fcntl.h>
//# include <sys/wait.h>
//# include <stdbool.h>
//# include "../../new_libft/libft.h"
# include "../../Includes/minishell.h"
//# include "parser.h"

// typedef enum e_tok_types
// {
// 	WORDS,
// 	OPTIONS,
// 	BUILTINS,
// 	PIPES,
// 	INFILES,
// 	OUTFILES,
// 	APPENDS,
// 	HEREDOCS,
// 	DOLLAR,
// 	S_QUOTE,
// 	D_QUOTE,
// 	LEFT_PAREN,
// 	RIGHT_PAREN,
// 	STAR,
// 	ANDS,
// 	ORS,
// 	CMD_SUB,
// 	EXIT_STAT,
// 	BACK_SLASH,
// 	NOTHING,
// }	t_type;

typedef struct s_toklist
{
	t_type				type;
	char				*lexeme;
	int					start_pos;
	int					lexeme_len;
	struct s_toklist	*next;
}	t_toklist;

typedef struct s_tokens
{
	t_type		l_t;
	int			size;
	t_toklist	*tail;
	t_toklist	*head;
	char		*t_input;
	int			lexeme_count;
	bool		is_inside_squote;
	bool		is_inside_dquote;
}	t_tokens;

char		*prompt1(t_tokens *tokens);
//t_tokens	*parse_line(t_tokens *tokens);
t_toklist	*scan_line(t_tokens *tokens);
bool		add_token(t_tokens *tokens, t_type types, char *lexeme, int s_pos);
void		init_tokens(t_tokens *tokens);
bool		add_pipe_or_op(t_tokens *tokens, char **c);
bool		add_infile_or_heredoc(t_tokens *tokens, char **c);
bool		add_outfile_or_append(t_tokens *tokens, char **c);
int			get_rest_of_lexeme(char **c, t_type type);
bool		add_variable(t_tokens *tokens, char **c);
t_type		get_type(char *c);
void		find_last_r_paren(char **c, char **s, t_tokens *tokens);
bool		wild_state(t_tokens *tokens, char **c);
bool		add_and(t_tokens *tokens, char **c);
bool		add_l_or_r_paren(t_tokens *tokens, char **c);
bool		add_literal(t_tokens *tokens, char **c);
bool		add_word_or_builtin(t_tokens *tokens, char **c);
//void		quoting_state(t_tokens *tokens, char **c);
//void		handle_quoting(t_tokens *tokens, t_type type, int len, char **s);
bool		is_builtin(char *lexeme);
bool		add_options(t_tokens *tokens, char **c);
bool		add_backslash(t_tokens *tokens, char **c);
void		prompt_for_more(t_tokens *tokens, char **c, char **s);
bool		is_delim(char c);
char		*expand(char *lexeme);
char		*get_heredoc_input(char *delim);
void		remove_escape_char(t_tokens *tokens);

#endif
