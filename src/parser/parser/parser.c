/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/19 06:44:31 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ***********************************************************************
 * If any of the tokens such as pipe, and, or, or last_backslash are     *
 * at the end of the tokens list, the function prompts for more, else    *
 * it simply returns the tokens t_input, which is used for managing      *
 * SIGINT if it was sent.                                                *
 * ***********************************************************************/
static void	*check_for_more_prompt(t_tokens *tokens,
	t_toklist *current, char **s)
{
	t_type	t;

	t = current->type;
	if ((t == PIPE || t == AND || t == OR || t == L_BACK_SLASH)
		&& !current->next)
	{
		if (!prompt_for_more(tokens, s, NULL))
			return (NULL);
		scan_line(tokens, s);
	}
	return (tokens->t_input);
}

/*
 * Depending on the case, a syntax error is printed.
 */
static void	syntax_error(int status, t_toklist *current, t_toklist *next_t)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if (status == 1)
		write(2, current->lexeme, ft_strlen(current->lexeme));
	else if (next_t && status == 2)
		write(2, next_t->lexeme, ft_strlen(next_t->lexeme));
	else if (!next_t && status == 2)
		write(2, "newline", 7);
	write(2, "'\n", 2);
}

/* ******************************************************************
 * This is basically the parser.                                    *
 * Takes a pointer to the current token being parsed, the last      *
 * token type parsed and the env list. l_t means last token.        *
 * Using the l_t parameter, it aims to check if the current token   *
 * is an expected token, if not it returns an error code.
 * It prompts for heredoc inputs and removes newlines from d_quote  *
 * and s_quote tokens entered during more prompts. It returns 0     *
 * if everything is fine.                                           *
 * ******************************************************************/
static int	check_tokens(t_toklist *current, t_type l_t, t_env *env)
{
	t_type			c_t;

	c_t = current->type;
	if ((c_t == PIPE || c_t == AND || c_t == OR)
		&& (l_t == PIPE || l_t == AND || l_t == OR || l_t == NOTHING))
		return (1);
	else if ((c_t == INFILE || c_t == OUTFILE || c_t == APPEND
			|| c_t == HEREDOC) && !*current->lexeme)
		return (2);
	else if (c_t == HEREDOC)
	{
		current->lexeme = get_heredoc_input(current->lexeme, env);
		if (!current->lexeme)
			return (130);
	}
	else if (c_t == S_QUOTE || c_t == D_QUOTE)
		current->lexeme = rm_newline(&current->lexeme);
	return (0);
}

/* **************************************************************
 * Parses the tokens, prints a syntax error in case of one and  *
 * prompts for more input when there is need. It returns        *
 * a status code, for syntax errors, sigint handling or 0       *
 * if everything is fine so far.                                *
 * **************************************************************/
static int	process_tokens(t_tokens *tokens, char **s, t_env *env)
{
	t_type		l_t;
	int			status;
	t_toklist	*current;

	status = 0;
	l_t = NOTHING;
	current = tokens->head;
	while (current)
	{
		status = check_tokens(current, l_t, env);
		if (status)
		{
			if (status != 130)
				syntax_error(status, current, current->next);
			return (status);
		}
		if (!check_for_more_prompt(tokens, current, s))
			return (130);
		l_t = current->type;
		current = current->next;
	}
	return (status);
}

/* **************************************************************
 * The parser in principle. It calls the scanner/lexer which    *
 * tokenizes the user input, Checks if we could ask for more    *
 * input, goes ahead to remove escape characters from back      *
 * slash tokens, expands variables, merge adjacent mergeable    *
 * tokens (E.g $USER$HOME are considered two tokens, however    *
 * they are joined together in the input, we need to make       *
 * sure after tokenizing and expansion they end up together as  *
 * one argument and not two arguments to the command).          *
 * Afterwards, the tokens are processed for syntax checks,      *
 * heredoc prompts etc. The parser after these, builds up the   *
 * executable command list which includes building redirection  *
 * list for every simple command.                               *
 * It returns a status code, with which the executor is called  *
 * or not.                                                      *
 * **************************************************************/
int	parse_tokens(t_command *cmd, t_tokens *tokens, t_env *env)
{
	char	*s;
	int		status;

	s = tokens->t_input;
	tokens->head = scan_line(tokens, &s);
	if (!tokens->head)
		return (130);
	check_for_more_back_slash_prompt(tokens, &s);
	remove_escape_char(tokens);
	expand_variables(tokens, env);
	merge_adjacent_tokens(tokens);
	status = process_tokens(tokens, &s, env);
	if (status == 130)
		return (status);
	if (status)
	{
		env->exit_status = 258;
		return (status);
	}
	join_cmd_and_args(cmd, tokens->head, env);
	enter_filelist(cmd, tokens->head);
	return (status);
}
