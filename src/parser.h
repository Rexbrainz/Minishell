/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 19:15:45 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <readline/readline.h>
# include <stdio.h>
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
	int					position;
	struct s_toklist	*next;
}	t_toklist;

typedef struct s_tokens
{
	t_toklist	*head;
	t_toklist	*tail;
	char		*user_input;
	int			lexemes_count;
	bool		is_inside_dquote;
	bool		is_inside_squote;
	int			size;
}	t_tokens;

t_tokens	*parse_line(t_tokens *tokens, char *line);
t_toklist	*scan_line(t_tokens *tokens);
bool		add_token(t_tokens *tokens, t_type types, char *token, int pos);
void		init_tokens(t_tokens *tokens, char *user_input);
bool		add_pipe_or_op(t_tokens *tokens, char **c);
bool		add_infile_or_heredoc(t_tokens *tokens, char **c);
bool		add_outfile_or_append(t_tokens *tokens, char **c);
int			get_rest_of_lexeme(char **c);
bool		add_variable(t_tokens *tokens, char **c);
bool		wild_state(t_tokens *tokens, char **c);
bool		add_and(t_tokens *tokens, char **c);

#endif
