/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/21 18:00:18 by sudaniel         ###   ########.fr       */
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

void	find_last_r_paren(char **s, int *i)
{
	while (**s && *i)
	{
		if (**s == '(')
			(*i)++;
		if (**s == ')')
			(*i)--;
		(*s)++;
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
		*s = tokens->user_input + len;
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
