/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:49:20 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/31 10:35:15 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"
//#include "scanner.h"
//#include "parser.h"

static char	*get_chars(char *lexeme, char **s, char *new_lexeme)
{
	char	*temp;
	char	*start;
	char	*chars;

	start = *s;
	while (**s && **s != '$')
	{
		if (**s == '\\' && *(*s + 1) == '$')
			(*s)++;
		(*s)++;
	}
	chars = ft_substr(lexeme, start - lexeme, *s - start);
	if (!chars)
		return (NULL);
	if (!new_lexeme)
		return (chars);
	temp = ft_strjoin(new_lexeme, chars);
	if (!temp)
		return (free(new_lexeme), NULL);
	free(new_lexeme);
	return (temp);
}

static char	*extract_var(char *lexeme, char **s, char *new_lexeme)
{
	char	*var;
	char	*temp;
	char	*start;

	start = *s;
	while (**s && **s != '$' && ft_isalnum(**s))
	{
		(*s)++;
		if (**s == '_')
			(*s)++;
	}
	temp = ft_substr(lexeme, start - lexeme, *s - start);
	if (!temp)
		return (NULL);
	var = getenv(temp);
	free(temp);
	if (!var && !new_lexeme)
		return (ft_strdup(""));
	if (!var && new_lexeme)
		return (new_lexeme);
	if (!new_lexeme)
		return (ft_strdup(var));
	temp = ft_strjoin(new_lexeme, var);
	free(new_lexeme);
	return (temp);
}

char	*expand(char *lexeme)
{
	char	*s;
	char	*temp;
	char	*new_lexeme;

	new_lexeme = NULL;
	s = lexeme;
	while (*s)
	{
		if (*s != '$')
		{
			temp = get_chars(lexeme, &s, new_lexeme);
			if (!temp)
				return (NULL);
			new_lexeme = temp;
		}
		else
		{
			s++;
			temp = extract_var(lexeme, &s, new_lexeme);
			if (!temp)
				return (NULL);
			new_lexeme = temp;
		}
	}
	return (free(lexeme), new_lexeme);
}

/*
void	perform_expansion(char	*str)
{
	char		*lexeme;

	while (current)
	{
		if (current->type == DOLLAR)
		{
			lexeme = getenv(current->lexeme + 1);
			free(current->lexeme);
			if (!lexeme)
				current->lexeme = ft_strdup("");
			else
				current->lexeme = ft_strdup(lexeme);
			if (!current->lexeme)
				current->lexeme = NULL;
		}

	lexeme = expansion(str);
	free(str);
	if (!lexeme)
		lexeme = NULL;
	return (lexeme);
}
*/
