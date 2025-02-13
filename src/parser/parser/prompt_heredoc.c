/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:55:19 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/12 08:32:50 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

static char	*check_for_quote(char *delim, bool *quote)
{
	int		i;
	char	c;
	int		len;
	char	*new_delim;

	len = ft_strlen(delim);
	new_delim = ft_calloc(len + 1, 1);
	i = 0;
	len = 0;
	while (delim[i])
	{
		if (delim[i] == '"' || delim[i] == '\'')
		{
			*quote = true;
			c = delim[i++];
			while (delim[i] && delim[i] != c)
				new_delim[len++] = delim[i++];
			if (delim[i])
				i++;
			continue ;
		}
		new_delim[len++] = delim[i++];
	}
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

static void	check_lexeme(char **lexeme, char *line)
{
	char	*temp;

	temp = NULL;
	if (!*lexeme)
		*lexeme = ft_strdup(line);
	else
	{
		temp = *lexeme;
		*lexeme = join_inputs(temp, line);
	}
	free(line);
}

static char	*the_prompt(char *delim)
{
	char	*line;
	char	*lexeme;

	lexeme = NULL;
	while (true)
	{
		line = readline("> ");
		if (!line || g_sigint_detected)
		{
			free(lexeme);
			g_sigint_detected = 0;
			return ("g_sigint_detected");
		}
		if (*line && !ft_strncmp(delim, line, ft_strlen(line)))
		{
			free(line);
			line = NULL;
			break ;
		}
		check_lexeme(&lexeme, line);
	}
	return (lexeme);
}

char	*get_heredoc_input(char *delim, t_env *env)
{
	bool	quote;
	char	*lexeme;

	signal(SIGINT, heredoc_sigint_handler);
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
		env->exit_status = 130;
		signal(SIGINT, main_sigint_handler);
		return (NULL);
	}
	if (!quote)
		lexeme = expand(lexeme, env);
	free(delim);
	return (lexeme);
}
