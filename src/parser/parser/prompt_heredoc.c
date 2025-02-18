/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:55:19 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 16:37:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* ********************************************************************
 * Takes the heredoc delim, and a pointer to a bool parameter.        *
 * If there are matching quotes, the bool parameter is updated and    *
 * all matching quotes in the delimeter are removed.                  *
 * The new delimeter is returned.                                     *
 * ********************************************************************/
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

/* ***********************************************************
 * The function takes a lexeme, which is basically the last  *
 * inputs entered by the user when prompted. it takes        *
 * the line string which is the recent input entered and     *
 * must be joined with lexeme, however before joining them   *
 * a new line character is entered in to the lexeme.         *
 * The function frees lexeme and returns the newly joined    *
 *  string.                                                  *
 * ***********************************************************/
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

/* *********************************************************
 * Checks the state of lexeme, if it is NULL, that means   *
 * it is the first time the prompt was called, in which    *
 * case the line is duplicated. otherwise line and lexeme  *
 * are joined together and line is freed.                  *
 * The function returns nothing.                           *
 * *********************************************************/
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

/* ***************************************************************
 * Prompts the user for inputs, if NULL was entered, all saved   *
 * lexemes are freed and null is returned. in case of sigint     *
 * a mechanism for handling sigint is used which causes the      *
 * function to return quickly.                                   *
 * Else until the user enters same input as the delimeter, it    *
 * keeps prompting and returns all input entered.                *
 * ***************************************************************/
static char	*the_prompt(char *delim)
{
	char	*line;
	char	*lexeme;

	lexeme = NULL;
	while (true)
	{
		line = readline("> ");
		if (!line)
			return (free(lexeme), lexeme = NULL, NULL);
		if (g_sigint_detected)
		{
			free(lexeme);
			g_sigint_detected = 0;
			return ("g_sigint_detected");
		}
		if (*line && !ft_strcmp(delim, line))
		{
			free(line);
			line = NULL;
			break ;
		}
		check_lexeme(&lexeme, line);
	}
	return (lexeme);
}

/* *****************************************************************
 * Takes the delimeter and env data struct to store exit status    *
 * when sigint is caught.                                          *
 * Installs sigint. checks if there are quotes in the delim,       *
 * removes all matching quotes, promts for user input and returns  *
 * the input, if there are no quotes, it tries to expand the       *
 * lexeme and returns the expanded lexeme                          *
 * *****************************************************************/
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
