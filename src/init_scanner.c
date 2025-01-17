/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scanner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 16:03:34 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Includes/minishell.h"

/*
 * TODO
 * subject to change*/
void	init_tokens(t_tokens *tokens, char *user_input)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->user_input = user_input;
	tokens->lexemes_count = 0;
	tokens->is_inside_dquote = false;
	tokens->is_inside_squote = false;
	tokens->size = 0;
}
