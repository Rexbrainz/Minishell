/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/25 14:24:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scanner.h"
#include "../../../Includes/minishell.h"

/*
 * TODO
 * subject to change*/
void	init_tokens(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->t_input = NULL;
	tokens->lexeme_count = 0;
	tokens->is_inside_squote = false;
	tokens->is_inside_dquote = false;
	tokens->is_heredoc_quote = false;
	tokens->l_t = -1;
	tokens->size = 0;
}
