/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:48:40 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 14:52:07 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

extern volatile sig_atomic_t	g_sigint_detected;
// Infile <, Outfile >, Append >>, Heredoc <<.
typedef enum e_types
{
	NO_REDIRECTION = -1,
	WORD,
	BUILTIN,
	PIPE,
	AND,
	OR,
	INFILE,
	OUTFILE,
	APPEND,
	HEREDOC,
	OPTIONS,
	DOLLAR,
	S_QUOTE,
	D_QUOTE,
	LEFT_PAREN,
	RIGHT_PAREN,
	STAR,
	CMD_SUB,
	EXIT_STAT,
	PID,
	BACK_SLASH,
	L_BACK_SLASH,
	NOTHING
}	t_type;

typedef struct s_envlist
{
	char				*key;
	char				*value;
	struct s_envlist	*next;	
}	t_envlist;

typedef struct s_env
{
	pid_t		pid;
	int			size;
	int			shlvl;
	t_envlist	*head;
	t_envlist	*tail;
	int			exit_status;
}	t_env;

#endif