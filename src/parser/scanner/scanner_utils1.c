/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/03 12:11:57 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../scanner.h"
#include "../../../Includes/minishell.h"

/*
 	Prompts for more input, when the input entered
	ends in a pipe |, or ||, or and && operator.
*/
void	prompt_for_more(t_tokens *tokens, char **c, char **s)
{
	int	c_len;
	int	s_len;

	c_len = ft_strlen(tokens->t_input);
	if (s)
		s_len = *s - tokens->t_input;
	prompt1(tokens);
	*c = tokens->t_input + c_len;
	if (s)
		*s = tokens->t_input + s_len;
}

bool	is_delim(char c)
{
	if (c == ' ' || c == ')' || c == '(' || c == '"'
		|| c == '\'' || c == '|' || c == '&'
		|| c == '<' || c == '>' || c == '\\')
		return (true);
	return (false);
}
