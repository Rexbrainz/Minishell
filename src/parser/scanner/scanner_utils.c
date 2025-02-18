/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 11:29:04 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/************************************************************************
 * A utility function for heredoc in the add_infile_or_heredoc function *
 * in add_lexeme.c file                                                 *
 * Takes the address of a pointer pointing to the user input,           *
 * The pointer is shifted two places ahead to skip the heredoc token    *
 * From there it searches for the end of the heredoc delimeter,         *
 * keeping track of quotes.                                             *
 * The fuction returns the length of the heredoc delimeter.             *
 * **********************************************************************/
int	get_heredoc_delim_len(char **c)
{
	char	ch;
	char	*s;

	s = NULL;
	(*c) += 2;
	while (**c && ft_isspace(**c))
		(*c)++;
	s = *c;
	while (*s && !ft_isspace(*s) && *s != '<' && *s != '>' && *s != '|'
		&& *s != '&')
	{
		if (*s == '\'' || *s == '"')
		{
			ch = *s;
			while (*s && *s != ch)
				s++;
		}
		s++;
	}
	return (s - *c);
}

/**********************************************************************
 * A utility function for the find_eot function in this file.         *
 * Takes the addresses of two pointers and the tokens list.           *
 * c points to the user input, while s points to the current          *
 * position of c and is used to iterate the user input from c.        *
 * c is needed here for cases when we need to prompt the user for     *
 * more input.                                                        *
 * s, used as the iterator searches for the matching right            *
 * parenthesis which marks the end of the token.                      *
 * ********************************************************************/
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

/* ************************************************************
 * A utility function for the add_word_or_bultin function in  *
 * add_lexeme2.c file.                                        *
 * Converts the lexeme taken as argument to lower case and    *
 * compares it against the builtins commands, it returns      *
 * true if the lexeme matches any of the builtins command     *
 * and false when not.                                        *
 * ************************************************************/
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

/* ********************************************************
 * A utility function to the add variable function in     *
 * add_lexeme.c file.                                     *
 * Takes a pointer to the char an index ahead of the      *
 * current token ($) to identify.                         *
 * Depending on what this character is, a token type is   *
 * returned.											  *
 * ********************************************************/
t_type	get_type(char *c)
{
	t_type	type;

	if (*c == '(')
		type = CMD_SUB;
	else if (*c == '?')
		type = EXIT_STAT;
	else if (*c == '$')
		type = PID;
	else if (*c == '_' || ft_isalpha(*c))
		type = DOLLAR;
	else
		type = WORD;
	return (type);
}

/* *********************************************************************
 * A utility function to the add variable function in                  *
 * add_lexeme.c file.												   *
 * Takes the tokens list, addresses of two pointers and a token type.  *
 * Depending on the token type the function searches for the end       *
 * of the lexeme.                                                      *
 * It returns nothing.                                                 *
 * *********************************************************************/
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
		while (**s && !is_delim(**s) && (ft_isalnum(**s) || **s == '_'))
			(*s)++;
	}
	else if (type == WORD)
	{
		(*s)++;
		while (**s && !is_delim(**s))
			(*s)++;
	}
}
