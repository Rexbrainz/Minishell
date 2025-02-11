/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:55:19 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/11 08:26:51 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

static char	*check_for_quote(char *delim, bool *quote)
{
	int		len;
	char	*new_delim;

	len = ft_strlen(delim);
	if ((*delim == '"' && delim[len - 1] == '"')
		|| (*delim == '\'' && delim[len - 1] == '\''))
	{
		*quote = true;
		new_delim = ft_substr(delim, 1, len - 2);
	}
	else
		new_delim = ft_strdup(delim);
	free(delim);
	return (new_delim);
}

static char	*join_inputs(char *lexeme, char *line)
{
	int		i;
	int		len;
	char	*temp;

	len = ft_strlen(lexeme);
	temp = (char *)malloc(len + 2);
	i = 0;
	while (lexeme[i])
	{
		temp[i] = lexeme[i];
		i++;
	}
	temp[i] = '\n';
	temp[i + 1] = '\0';
	free(lexeme);
	lexeme = ft_strjoin(temp, line);
	free(temp);
	return (lexeme);
}

static char	*the_prompt(char *delim)
{
	char	*line;
	char	*temp;
	char	*lexeme;

	lexeme = NULL;
	while (true)
	{
		line = readline("> ");
		if (*line && !ft_strncmp(delim, line, ft_strlen(line)))
		{
			free(line);
			line = NULL;
			break ;
		}
		if (g_sigint_detected)
		{
			free(lexeme);
			rl_replace_line("", 0);
			return ("g_sigint_detected");
		}
		if (!lexeme)
			lexeme = ft_strdup(line);
		else
		{
			temp = join_inputs(lexeme, line);
			lexeme = temp;
		}
		free(line);
	}
	return (lexeme);
}

char	*get_heredoc_input(char *delim, t_env *env)
{
	bool	quote;
	char	*lexeme;

	lexeme = NULL;
	quote = false;
	delim = check_for_quote(delim, &quote);
	if (!delim)
		return (NULL);
	lexeme = the_prompt(delim);
	if (!lexeme)
		return (free(delim), delim = NULL, ft_strdup(""));
	if (!ft_strncmp(lexeme, "g_sigint_detected", ft_strlen(lexeme)))
	{
		ft_printf("We returned NULL\n");
		return (NULL);
	}
	if (!quote)
		lexeme = expand(lexeme, env);
	free(delim);
	return (lexeme);
}
