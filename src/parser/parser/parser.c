/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/04 18:58:26 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"
static void	expand_tokens(t_tokens *tokens)
{
	t_toklist	*current;

	current = tokens->head;
	while (current)
	{
		if (current->type == DOLLAR || current->type == D_QUOTE)
			current->lexeme = expand(current->lexeme);
		current = current->next;
	}
}

static void	
	check_for_more_prompt(t_tokens *tokens, t_toklist *current, char **s)
{
	t_type	t;

	t = current->type;
	if ((t == PIPE || t == AND || t == OR || t == BACK_SLASH)
		&& !current->next)
	{
		prompt_for_more(tokens, s, NULL);
		scan_line(tokens, s);
	}
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

static int	process_tokens(t_toklist *current, t_type l_t)
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
		current->lexeme = get_heredoc_input(current->lexeme);
	return (0);
}

int	parse_tokens(t_command *cmd, t_tokens *tokens, char **env)
{
	char		*s;
	t_type		l_t;
	int			status;
	t_toklist	*current;

	s = tokens->t_input;
	tokens->head = scan_line(tokens, &s);
	current = tokens->head;
	l_t = NOTHING;
	status = -1;
	current = tokens->head;
	while (current)
	{
		status = process_tokens(current, l_t);
		if (status)
		{
			syntax_error(status, current, current->next);
			return (status);
		}
		check_for_more_prompt(tokens, current, &s);
		l_t = current->type;
		current = current->next;
	}
	if (tokens->lexeme_count == 1 && !*tokens->head->lexeme)
		return (-1);
	remove_escape_char(tokens);
	expand_tokens(tokens);
	join_cmd_and_args(cmd, tokens->head, env);
	enter_filelist(cmd, tokens->head);
	return (status);
}
