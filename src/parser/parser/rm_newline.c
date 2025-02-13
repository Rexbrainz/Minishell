/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_newline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 06:42:22 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/05 07:30:09 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

char	*check_for_more_back_slash_prompt(t_tokens *tokens, char **s)
{
	t_toklist	*curr;

	curr = tokens->head;
	while (curr)
	{
		if (curr->type == L_BACK_SLASH)
		{
			if (!prompt_for_more(tokens, s, NULL))
				return (NULL);
			scan_line(tokens, s);
		}
		curr = curr->next;
	}
	return (tokens->t_input);
}

char	*get_new_lexeme(char *lexeme)
{
	int		i;
	int		len;
	char	*new_lexeme;

	i = 0;
	len = 0;
	while (lexeme[i])
		if (lexeme[i++] != '\n')
			len++;
	new_lexeme = (char *)malloc(len + 1);
	if (!new_lexeme)
		return (NULL);
	i = 0;
	len = 0;
	while (lexeme[i])
	{
		if (lexeme[i] != '\n')
			new_lexeme[len++] = lexeme[i];
		i++;
	}
	new_lexeme[len] = '\0';
	return (new_lexeme);
}

char	*rm_newline(char **lexeme)
{
	char	*find;
	char	*new_lexeme;

	find = NULL;
	find = ft_strchr(*lexeme, '\n');
	if (!find)
		return (*lexeme);
	new_lexeme = get_new_lexeme(*lexeme);
	free(*lexeme);
	*lexeme = NULL;
	return (new_lexeme);
}
