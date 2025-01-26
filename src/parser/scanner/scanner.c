/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:54 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/24 12:19:39 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../scanner.h"

bool	add_token(t_tokens *tokens, t_type types, char *lexeme, int s_pos)
{
	t_toklist	*new_node;

	new_node = (t_toklist *)malloc(sizeof(t_toklist));
	if (!new_node)
		return (false);
	new_node->lexeme = lexeme;
	new_node->type = types;
	new_node->lexeme_len = ft_strlen(lexeme);
	new_node->start_pos = s_pos;
	new_node->next = NULL;
	if (!tokens->head)
	{
		tokens->head = new_node;
		tokens->tail = new_node;
	}
	else
	{
		tokens->tail->next = new_node;
		tokens->tail = new_node;
	}
	tokens->lexeme_count++;
	tokens->size++;
	return (true);
}

static bool	id_and_add_tokens(t_tokens *tokens, char **c)
{
	if ((**c == '-') && !add_options(tokens, c))
		return (false);
	else if (**c == '\\' && !add_backslash(tokens, c))
		return (false);
	else if (**c == '|' && !add_pipe_or_op(tokens, c))
		return (false);
	else if ((**c == '\'' || **c == '"') && !add_literal(tokens, c))
		return (false);
	else if (**c == '*' && !wild_state(tokens, c))
		return (false);
	else if (**c == '$' && !add_variable(tokens, c))
		return (false);
	else if ((**c == '(' || **c == ')') && !add_l_or_r_paren(tokens, c))
		return (false);
	else if (**c == '<' && !add_infile_or_heredoc(tokens, c))
		return (false);
	else if (**c == '>' && !add_outfile_or_append(tokens, c))
		return (false);
	else if (**c == '&' && *(*c + 1) == '&' && !add_and(tokens, c))
		return (false);
	return (true);
}

static bool	add_word_or_builtin(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	while (**c && (**c != ' ' && **c != ')' && **c
			!= '(' && **c != '"' && **c != '\'' && **c != '\\'
			&& **c != '|' && **c != '&' && **c != '$'
			&& **c != '<' && **c != '>'))
		(*c)++;
	lexeme = ft_substr(tokens->t_input, s - tokens->t_input, *c - s);
	if (!lexeme)
		return (false);
	if (is_builtin(lexeme))
	{
		if (!add_token(tokens, BUILTINS, lexeme, s - tokens->t_input))
			return (false);
		tokens->l_t = BUILTINS;
	}
	else
	{
		if (!add_token(tokens, WORDS, lexeme, s - tokens->t_input))
			return (false);
		tokens->l_t = WORDS;
	}
	return (true);
}

t_toklist	*scan_line(t_tokens *tokens)
{
	char	*s;

	s = tokens->t_input;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (ft_isalnum(*s))
		{
			if (!add_word_or_builtin(tokens, &s))
				return (NULL);
			continue ;
		}
		if (*s == '$' && (*(s + 1) == ' ' || !*(s + 1)) && !add_token(tokens,
				WORDS, ft_strdup("$"), s++ - tokens->t_input))
			return (NULL);
		if (!id_and_add_tokens(tokens, &s))
			return (NULL);
		if (!*s && (tokens->l_t == ANDS
				 || tokens->l_t == ORS || tokens->l_t == PIPES
				 || tokens->l_t == BACK_SLASH))
			prompt_for_more(tokens, &s);
	}
	return (tokens->head);
}
