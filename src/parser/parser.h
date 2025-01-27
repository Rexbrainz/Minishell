/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:48:09 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/27 08:27:45 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../Includes/minishell.h"
# include "scanner.h"

typedef struct file_list
{
	t_type				type;
	char				*file_name;
	struct file_list	*next;
}	t_files;

typedef struct cmdlist
{
	char			**cmd;
	t_type			type;
	t_files			*files;
	struct cmdlist	*next;
}	t_cmds;

typedef struct cmd
{
	int		size;
	t_cmds	*head;
	t_cmds	*tail;
}	t_cmd;

bool	add_cmd(t_cmd *cmd, char **cmd_args, t_type type, t_files *files);
void	split_into_cmds(t_cmd *cmd, t_tokens *tokens);
char	*expand(char *lexeme);
char	*get_heredoc_input(char *delim);
void	remove_escape_char(t_tokens *tokens);

#endif
