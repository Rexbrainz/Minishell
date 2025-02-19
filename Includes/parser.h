/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/19 07:15:06 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// tokens list
typedef struct s_toklist
{
	t_type				type; // token type
	char				*lexeme; // the lexeme associated with token type
	int					end_pos; // end position of the lexeme in the input
	int					start_pos; // start position of the lexeme
	int					lexeme_len; // length of the lexeme
	struct s_toklist	*next; // next token
}	t_toklist;

// Info and access to the tokens list
typedef struct s_tokens
{
	t_toklist	*tail; // pointer to the last token in the tokens list
	t_toklist	*head; // pointer to the first token in the tokens list
	char		*t_input; // User input
	int			lexeme_count; // Number of tokens found. similar to size
	bool		backslash_inside_word; // backlash found in a lexeme
}	t_tokens;

char		*prompt1(t_tokens *tokens);

// Scanner
void		init_tokens(t_tokens *tokens);
bool		is_delim(char c);
bool		add_token(t_tokens *tokens, t_type types, char *lexeme, int s_pos);
bool		add_pipe_or_op(t_tokens *tokens, char **c);
bool		add_infile_or_heredoc(t_tokens *tokens, char **c);
bool		add_outfile_or_append(t_tokens *tokens, char **c);
int			get_heredoc_delim_len(char **c);
int			get_filelen(char **c, t_type type);
bool		add_variable(t_tokens *tokens, char **c);
t_type		get_type(char *c);
void		find_eot(t_tokens *tokens, char **c, char **s, t_type type);
void		find_last_r_paren(char **c, char **s, t_tokens *tokens);
bool		wild_state(t_tokens *tokens, char **c);
bool		add_and(t_tokens *tokens, char **c);
bool		add_l_or_r_paren(t_tokens *tokens, char **c);
bool		add_literal(t_tokens *tokens, char **c);
bool		add_word_or_builtin(t_tokens *tokens, char **c);
bool		is_builtin(char *lexeme);
bool		add_options(t_tokens *tokens, char **c);
bool		add_backslash(t_tokens *tokens, char **c);

// Parser
t_toklist	*scan_line(t_tokens *tokens, char **s);
char		*prompt_for_more(t_tokens *tokens, char **c, char **s);
void		expand_variables(t_tokens *tokens, t_env *env);
char		*expand(char *lexeme, t_env *env);
char		*expand_dollar(char *lexeme, t_toklist	*current,
				t_tokens *tokens, t_env *env);
char		*get_var_and_expand(char *lexeme, char **s, t_env *env);
char		*remove_space_after_expansion(char *retval);
char		*get_heredoc_input(char *delim, t_env *env);
void		remove_escape_char(t_tokens *tokens);
char		*rm_newline(char **lexeme);
char		*check_for_more_back_slash_prompt(t_tokens *tokens, char **s);
void		merge_adjacent_tokens(t_tokens *tokens);

#endif
