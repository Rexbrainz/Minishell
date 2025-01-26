/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lexemes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:03:32 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/23 14:46:47 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
#include "../scanner.h"

bool	add_options(t_tokens *tokens, char **c)
{
	char	*s;
	char	*lexeme;

	s = *c;
	while (*s)
	{
		if (*s++ == ' ')
		{
			while (ft_isspace(*s))
				s++;
			if (*s != '-')
				break ;
		}
	}
	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, s - *c);
	if (!lexeme || !add_token(tokens, OPTIONS, lexeme, *c - tokens->t_input))
		return (false);
	tokens->l_t = OPTIONS;
	*c = s;
	return (true);
}

bool	add_backslash(t_tokens *tokens, char **c)
{
	char	*lexeme;

	lexeme = ft_substr(tokens->t_input, *c - tokens->t_input, 2);
	if (!lexeme
	 || !add_token(tokens, BACK_SLASH, lexeme, *c - tokens->t_input))
	 	return (false);
	tokens->l_t = BACK_SLASH;
	*c += 2;
	return (true);
}
