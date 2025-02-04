/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/04 17:52:35 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../scanner.h"
#include "../../../Includes/minishell.h"

void	init_tokens(t_tokens *tokens)
{
	tokens->head = NULL;
	tokens->tail = NULL;
	tokens->t_input = NULL;
	tokens->lexeme_count = 0;
	tokens->is_inside_squote = false;
	tokens->is_inside_dquote = false;
	tokens->backslash_inside_word = false;
}

void	init_commands(t_command *cmd)
{
	cmd->head = NULL;
	cmd->tail = NULL;
	cmd->size = 0;
}
