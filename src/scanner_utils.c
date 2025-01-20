/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/20 13:53:29 by sudaniel         ###   ########.fr       */
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
		while (*s == '<' || ft_isspace(*s))
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

char	*manage_before_prompt1(char **c)
{
	char	*s;
	int		len;

	len = ft_strlen(*c);
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	ft_strlcpy(s, *c, len + 1);
	return (s);
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
		while (ft_tolower(lexeme[j]) == builtins[i][j])
			j++;
		if (!lexeme[j] && !builtins[i][j])
			return (true);
		i++;
	}
	return (false);
}
