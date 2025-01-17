/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 10:06:08 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

t_tokens	*parse_line(t_tokens *tokens, char *line)
{
	char	*input;

	input = ft_strtrim(line, "\t\n ");
	if (!input)
		return (NULL);
	init_tokens(tokens, input);
	tokens->head = scan_line(tokens);
	return (tokens);
}
