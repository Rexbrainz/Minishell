/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/22 15:14:16 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Includes/minishell.h"

int	get_rest_of_lexeme(char **c, t_type type)
{
	char	*s;

	s = *c;
	if (type == INFILES || type == HEREDOCS)
	{
		while (*s && (*s == '<' || ft_isspace(*s)))
			s++;
		while (*s && *s != ' ')
			s++;
	}
	else if (type == OUTFILES || type == APPENDS)
	{
		while (*s == '>' || ft_isspace(*s))
			s++;
		while (*s && *s != ' ')
			s++;
	}
	return (s - *c);
}

void	find_last_r_paren(char **c, char **s, int *i, t_tokens *tokens)
{
	int	current_len;
	int	start_of_token_len;

	while (*i)
	{
		if (**s == '(')
			(*i)++;
		if (**s == ')')
			(*i)--;
		(*s)++;
		if (!**s && *i)
		{
			ft_printf("%d\n", *i);
			current_len = *s - tokens->t_input;
			start_of_token_len = *c - tokens->t_input;
			tokens->t_input = prompt1(tokens);
			if (!tokens->t_input)
				return ;
			*s = tokens->t_input + current_len;
			*c = tokens->t_input + start_of_token_len;
		}
	}
}

void	handle_quoting(t_tokens *tokens, t_type type, int len, char **s)
{
	char	c;
	char	*p;

	if (type == D_QUOTE)
		c = '"';
	else
		c = '\'';
	p = NULL;
	while (true)
	{
		prompt1(tokens);
		*s = tokens->t_input + len;
		p = ft_strchr(*s + 1, c);
		if (p)
			break ;
	}
}

bool	is_builtin(char *lexeme)
{
	int		i;
	int		j;
	char	*builtins[7];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	i = 0;
	while (i < 7)
	{
		j = 0;
		while (lexeme[j] && ft_tolower(lexeme[j]) == builtins[i][j])
			j++;
		if (!lexeme[j] && !builtins[i][j])
			return (true);
		i++;
	}
	return (false);
}

t_type	get_type(char *c)
{
	t_type	type;

	if (*c == '(')
		type = CMD_SUB;
	else if (*c == '?')
		type = EXIT_STAT;
	else
		type = DOLLAR;
	return (type);
}
