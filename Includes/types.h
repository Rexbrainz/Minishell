/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:48:40 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/17 08:39:00 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

extern volatile sig_atomic_t	g_sigint_detected;

/*
		All the types of input to be identified
	a way to communicate between parsing & execution
*/
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

typedef struct s_envlist // char **env into a list
{
	char				*key;
	char				*value;
	struct s_envlist	*next;
}	t_envlist;

typedef struct s_env // Controling struct for env
{
	pid_t		pid; // extra information put here for easy access
	int			size;
	int			shlvl; // help to handle an edge case
	t_envlist	*head;
	t_envlist	*tail;
	int			exit_status; // same as for pid above
}	t_env;

#endif
