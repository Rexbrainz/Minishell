/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:53:24 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/15 17:59:34 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <unistd.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef enum e_tok
{
	WORDS,
	BUILTINS,
	PIPES,
	INFILES,
	OUTFILES,
	APPENDS,
	HEREDOCS,
	S_QUOTE_OPEN,
	S_QUOTE_CLOSE,
	D_QUOTE_OPEN,
	D_QUOTE_CLOSE,
	LEFT_PAREN,
	RIGHT_PAREN,
	STAR
}	t_tokens;

typedef struct s_toklist
{
	char				*name;
	t_tokens			type;
	struct s_toklist	*next;
}	t_toklist;

typedef struct s_tokens
{
	t_toklist	*head;
	t_toklist	*tail;
	int			size;
}	t_tok_access;

t_toklist	*parse_line(char *line);
t_toklist	*scan_line(char *line);
#endif
