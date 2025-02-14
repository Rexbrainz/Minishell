/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_and_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:02:51 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/14 10:43:37 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	cmd->size = 0;
	cmd->head = NULL;
	cmd->tail = NULL;
}
