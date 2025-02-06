/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:49:20 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/06 16:25:35 by sudaniel         ###   ########.fr       */
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
			new_lexeme = temp;
		}
		else
		{
			s++;
			temp = extract_var(lexeme, &s, new_lexeme);
			if (!temp)
				return (free(lexeme), NULL);
			new_lexeme = temp;
		}
	}
	if (!new_lexeme)
		new_lexeme = ft_strdup("");
	return (free(lexeme), new_lexeme);
}

void	expand_variables(t_tokens *tokens)
{
	t_toklist	*current;

	current = tokens->head;
	while (current)
	{
		if (current->type == DOLLAR || current->type == D_QUOTE)
			current->lexeme = expand(current->lexeme);
		current = current->next;
	}
}
