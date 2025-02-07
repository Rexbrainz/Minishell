/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/07 08:00:34 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../scanner.h"
#include "../../../Includes/minishell.h"

int	get_rest_of_lexeme(char **c, t_type type)
{
	char	*s;

	s = NULL;
	if (type == INFILE || type == HEREDOC)
	{
		while (**c && (**c == '<' || ft_isspace(**c)))
			(*c)++;
		s = *c;
		while (*s && *s != ' ' && *s != '<' && *s != '>' && *s != '|'
			&& *s != '&')
			s++;
	}
	else if (type == OUTFILE || type == APPEND)
	{
		while (**c == '>' || ft_isspace(**c))
			(*c)++;
		s = *c;
		while (*s && *s != ' ' && *s != '<' && *s != '>' && *s != '|'
			&& *s != '&')
			s++;
	}
	return (s - *c);
}

void	find_last_r_paren(char **c, char **s, t_tokens *tokens)
{
	int	i;
	int	current_len;
	int	start_of_token_len;

	i = 0;
	while (**s)
	{
		if (**s == '(')
			i++;
		else if (**s == ')')
			i--;
		if (**s == ')' && !i)
			break ;
		(*s)++;
		if (!**s && i)
		{
			current_len = *s - tokens->t_input;
			start_of_token_len = *c - tokens->t_input;
			tokens->t_input = prompt1(tokens);
			if (!tokens->t_input)
				return ;
			*s = tokens->t_input + current_len;
			*c = tokens->t_input + start_of_token_len;
		}
	}
}
/*
void	handle_quoting(t_tokens *tokens, t_type type, int len, char **s)
{
	char	c;
	char	*p;

	if (type == D_QUOTE)
		c = '"';
	else
		c = '\'';
	p = NULL;
	while (true)
	{
		prompt1(tokens);
		*s = tokens->t_input + len;
		p = ft_strchr(*s + 1, c);
		if (p)
			break ;
	}
}
*/

bool	is_builtin(char *lexeme)
{
	int		i;
	int		j;
	char	*builtins[7];

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	i = 0;
	while (i < 7)
	{
		j = 0;
		while (lexeme[j] && ft_tolower(lexeme[j]) == builtins[i][j])
			j++;
		if (!lexeme[j] && !builtins[i][j])
			return (true);
		i++;
	}
	return (false);
}

t_type	get_type(char *c)
{
	t_type	type;

	if (*c == '(')
		type = CMD_SUB;
	else if (*c == '?')
		type = EXIT_STAT;
	else if (*c == '$')
		type = PID;
	else if (!*c || ft_isspace(*c))
		type = WORD;
	else
		type = DOLLAR;
	return (type);
}

void	find_eot(t_tokens *tokens, char **c, char **s, t_type type)
{
	if (type == CMD_SUB)
	{
		find_last_r_paren(c, s, tokens);
		(*s)++;
	}
	else if (type == DOLLAR)
	{
		(*s)++;
		while (**s && !is_delim(**s) && **s != '$')
			(*s)++;
	}
}
