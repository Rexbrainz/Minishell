/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/14 10:47:07 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_toklist
{
	t_type				type;
	char				*lexeme;
	int					end_pos;
	int					start_pos;
	int					lexeme_len;
	struct s_toklist	*next;
}	t_toklist;

typedef struct s_tokens
{
	t_toklist	*tail;
	t_toklist	*head;
	char		*t_input;
	int			lexeme_count;
	bool		is_inside_squote;
	bool		is_inside_dquote;
	bool		backslash_inside_word;
}	t_tokens;

char		*prompt1(t_tokens *tokens);
t_toklist	*scan_line(t_tokens *tokens, char **s);
bool		add_token(t_tokens *tokens, t_type types, char *lexeme, int s_pos);
void		init_tokens(t_tokens *tokens);
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
char		*prompt_for_more(t_tokens *tokens, char **c, char **s);
bool		is_delim(char c);
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
