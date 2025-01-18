/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/18 19:05:03 by sudaniel         ###   ########.fr       */
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

/*
 * TODO: Still buggy, but close.
 */
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
		if (p && type == S_QUOTE)
			break ;
		else if (p && type == D_QUOTE)
		{
			if (*(p - 1) != '\\')
				break ;
			len += p - *s;
		}
	}
}
