/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/20 14:21:21 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../new_libft/libft.h"
# include "../Includes/minishell.h"

typedef enum e_tok_types
{
	WORDS,
	BUILTINS,
	PIPES,
	INFILES,
	OUTFILES,
	APPENDS,
	HEREDOCS,
	DOLLAR,
	S_QUOTE,
	D_QUOTE,
	LEFT_PAREN,
	RIGHT_PAREN,
	STAR,
	ANDS,
	ORS,
	CMD_SUB,
	EXIT_STAT
}	t_type;

typedef struct s_toklist
{
	char				*lexeme;
	t_type				type;
	int					start_pos;
	struct s_toklist	*next;
}	t_toklist;

typedef struct s_tokens
{
	t_toklist	*head;
	t_toklist	*tail;
	char		*user_input;
	char		*t_input;
	int			lexeme_count;
	bool		is_inside_squote;
	bool		is_inside_dquote;
	int			size;
}	t_tokens;

char		*prompt1(t_tokens *tokens);
t_tokens	*parse_line(t_tokens *tokens);
t_toklist	*scan_line(t_tokens *tokens);
bool		add_token(t_tokens *tokens, t_type types, char *token, int s_pos);
void		init_tokens(t_tokens *tokens);
bool		add_pipe_or_op(t_tokens *tokens, char **c);
bool		add_infile_or_heredoc(t_tokens *tokens, char **c);
bool		add_outfile_or_append(t_tokens *tokens, char **c);
int			get_rest_of_lexeme(char **c, t_type type);
bool		add_variable(t_tokens *tokens, char **c);
bool		wild_state(t_tokens *tokens, char **c);
bool		add_and(t_tokens *tokens, char **c);
bool		add_l_or_r_paren(t_tokens *tokens, char **c);
bool		add_literal(t_tokens *tokens, char **c);
void		handle_quoting(t_tokens *tokens, t_type type, int len, char **s);
bool		is_builtin(char *lexeme);

#endif
