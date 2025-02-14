/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/14 10:43:49 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/*
 	Prompts for more input, when the input entered
	ends in a pipe |, or ||, or and && operator.
*/
char	*prompt_for_more(t_tokens *tokens, char **c, char **s)
{
	int	c_len;
	int	s_len;

	signal(SIGINT, heredoc_sigint_handler);
	c_len = ft_strlen(tokens->t_input);
	if (s)
		s_len = *s - tokens->t_input;
	if (!prompt1(tokens))
	{
		signal(SIGINT, main_sigint_handler);
		return (NULL);
	}
	*c = tokens->t_input + c_len;
	if (s)
		*s = tokens->t_input + s_len;
	return (tokens->t_input);
}

int	get_filelen(char **c, t_type type)
{
	char	*s;

	(*c)++;
	if (type == APPEND || type == HEREDOC)
		(*c)++;
	while (**c && ft_isspace(**c))
		(*c)++;
	s = *c;
	while (*s && !is_delim(*s))
		s++;
	return (s - *c);
}

bool	is_delim(char c)
{
	if (ft_isspace(c) || c == ')' || c == '(' || c == '"'
		|| c == '\'' || c == '|' || c == '&' || c == '$'
		|| c == '<' || c == '>' || c == '\\')
		return (true);
	return (false);
}
