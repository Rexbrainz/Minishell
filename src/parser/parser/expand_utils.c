/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:38:27 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/13 12:09:45 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"

char	*get_var_and_expand(char *lexeme, char **s, t_env *env)
{
	char	*var;
	char	*start;
	char	*value;

	start = *s;
	while (**s && **s != '$' && ft_isalnum(**s))
	{
		(*s)++;
		if (**s == '_')
			(*s)++;
	}
	var = ft_substr(lexeme, start - lexeme, *s - start);
	value = get_env(var, env);
	free(var);
	return (value);
}

char	*remove_space_after_expansion(char *retval)
{
	int		i;
	int		len;
	char	*removed_spaces;

	len = ft_strlen(retval);
	removed_spaces = ft_calloc(len + 1, 1);
	i = 0;
	len = 0;
	while (ft_isspace(retval[i]))
		i++;
	while (retval[i])
	{
		if (ft_isspace(retval[i]))
		{
			while (ft_isspace(retval[i]))
				i++;
			if (retval[i])
				removed_spaces[len++] = ' ';
		}
		removed_spaces[len++] = retval[i++];
	}
	free(retval);
	return (removed_spaces);
}

static char	*remove_space_for_dollar(char *retval,
	t_toklist *prev, t_toklist *next)
{
	int		i;
	int		len;
	char	*removed_spaces;

	removed_spaces = ft_calloc(ft_strlen(retval) + 1, 1);
	i = 0;
	len = 0;
	while (ft_isspace(retval[i]))
		i++;
	if (i != 0 && prev != NULL)
		removed_spaces[len++] = ' ';
	while (retval[i])
	{
		if (ft_isspace(retval[i]))
		{
			while (ft_isspace(retval[i]))
				i++;
			if (retval[i])
				removed_spaces[len++] = ' ';
			if (retval[i] == '\0' && next != NULL)
				removed_spaces[len++] = ' ';
		}
		removed_spaces[len++] = retval[i++];
	}
	return (free(retval), removed_spaces);
}

char	*expand_dollar(char *lexeme, t_toklist	*current,
	t_tokens *tokens, t_env *env)
{
	char		*value;
	t_toklist	*prev;
	t_toklist	*next;
	t_toklist	*tmp;
	char		*return_value;

	prev = NULL;
	tmp = tokens->head;
	while (tmp != current)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	next = current->next;
	value = get_env(lexeme + 1, env);
	if (!value)
		return (free(lexeme), ft_strdup(""));
	if (prev || next)
		return_value = remove_space_for_dollar(value, prev, next);
	else
		return_value = remove_space_after_expansion(value);
	return (free(lexeme), return_value);
}
