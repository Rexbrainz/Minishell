/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:29 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/18 16:34:11 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

t_tokens	*parse_line(t_tokens *tokens)
{
	if (!tokens->t_input)
		return (NULL);
//	tokens->head = scan_line(tokens);
	return (tokens);
}
