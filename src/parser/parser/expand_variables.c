/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 06:49:20 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/12 15:51:36 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

char	*get_env(char *lexeme, t_env *env)
{
	t_envlist	*curr;

	if (!ft_strcmp(lexeme, "$$"))
		return (ft_itoa(env->pid));
	else if (!ft_strcmp(lexeme, "$?"))
		return (ft_itoa(env->exit_status));
	curr = env->head;
	while (curr)
	{
		if (!ft_strcmp(lexeme, curr->key))
		{
			if (!curr->value)
				break ;
			return (ft_strdup(curr->value + 1));
		}
		curr = curr->next;
	}
	return (NULL);
}

static char	*get_chars(char *lexeme, char **s, char *new_lexeme)
{
	char	*temp;
	char	*start;
	char	*chars;

	start = *s;
	if (**s == '$')
		(*s)++;
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
		return (free(chars), free(new_lexeme), NULL);
	free(chars);
	free(new_lexeme);
	return (temp);
}

static char	*extract_var(char *lexeme, char **s, char *new_lexeme,
	t_env *env)
{
	char	*var;
	char	*temp;

	var = get_var_and_expand(lexeme, s, env);
	if (!var && !new_lexeme)
		return (free(var), ft_strdup(""));
	if (!var && new_lexeme)
		return (new_lexeme);
	temp = remove_space_after_expansion(var);
	if (!new_lexeme)
		return (temp);
	var = ft_strjoin(new_lexeme, temp);
	free(new_lexeme);
	return (free(temp), var);
}

char	*expand(char *lexeme, t_env *env)
{
	char	*s;
	char	*temp;
	char	*new_lexeme;

	new_lexeme = NULL;
	s = lexeme;
	while (*s)
	{
		if (*s != '$' || (*(s + 1) != '_' && !ft_isalpha(*(s + 1))))
		{
			temp = get_chars(lexeme, &s, new_lexeme);
			new_lexeme = temp;
		}
		else
		{
			s++;
			temp = extract_var(lexeme, &s, new_lexeme, env);
			if (!temp)
				return (free(lexeme), NULL);
			new_lexeme = temp;
		}
	}
	if (!new_lexeme)
		new_lexeme = ft_strdup("");
	return (free(lexeme), new_lexeme);
}

void	expand_variables(t_tokens *tokens, t_env *env)
{
	t_type		t;
	char		*temp;
	t_toklist	*cur;

	cur = tokens->head;
	while (cur)
	{
		t = cur->type;
		if (t == D_QUOTE && !ft_strcmp(cur->lexeme, "$?"))
		{
			t = EXIT_STAT;
			cur->type = EXIT_STAT;
		}
		if (t == D_QUOTE)
			cur->lexeme = expand(cur->lexeme, env);
		else if (t == DOLLAR)
			cur->lexeme = expand_dollar(cur->lexeme, cur, tokens, env);
		else if (t == PID || t == EXIT_STAT)
		{
			temp = cur->lexeme;
			cur->lexeme = get_env(cur->lexeme, env);
			free(temp);
		}
		cur = cur->next;
	}
}
