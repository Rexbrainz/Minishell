/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/13 13:54:54 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

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
