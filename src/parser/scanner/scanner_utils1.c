/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/25 15:19:44 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scanner.h"
#include "../../../Includes/minishell.h"

/*
 	Prompts for more input, when the input entered
	ends in a pipe |, or ||, or and && operator.
*/
void	prompt_for_more(t_tokens *tokens, char **c)
{
	int	len;

	len = ft_strlen(tokens->t_input);
	prompt1(tokens);
	*c = tokens->t_input + len;
}

bool	is_delim(char c)
{
	if (c == ' ' || c == ')' || c == '(' || c == '"'
		 || c == '\'' || c == '|' || c != '&' || c != '$'
		 || c == '<' || c == '>' || c == '\\')
		 return (true);
	return (false);
}
/*
static char	*check_for_quote(char *delim)
{
	char	*new_delim;

	if (*delim == '"' || *delim == '\'')
		new_delim = ft_substr(delim, 1, ft_strlen(delim) - 2);
	else
		new_delim = delim;
	free(delim);
	return (new_delim);
}

static char	*join_inputs(char *lexeme, char *line)
{
	int		i;
	int		len;
	char	*temp;

	len = ft_strlen(lexeme);
	temp = (char *)malloc(len + 1);
	i = 0;
	while (lexeme[i])
	{
		temp[i] = lexeme[i];
		i++;
	}
	temp[i] = '\n';
	temp[i + 1] = '\0';
	free(lexeme);
	return (ft_strjoin(temp, line));
}

char	*get_heredoc_input(char *delim)
{
	char	*line;
	char	*temp;
	char	*lexeme;

	lexeme = NULL;
	if (!delim)
		return (NULL);
	while (true)
	{
		line = readline("> ");
		if (!ft_strncmp(delim, line, ft_strlen(delim)))
			break ;
		if (!lexeme)
			lexeme = ft_strdup(line);
		else
		{
			temp = join_inputs(lexeme, line);
			lexeme = temp;
		}
		if (!lexeme)
			return (NULL);
	}
	free(delim);
	return (lexeme);
}
*/