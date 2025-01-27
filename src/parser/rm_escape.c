/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:39:09 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/27 12:36:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/minishell.h"
#include "scanner.h"
#include "parser.h"

static char	*rm_backslash(char *lexeme)
{
	int		i;
	int		len;
	char	*temp;

	len = ft_strlen(lexeme);
	temp = ft_calloc(len, sizeof(char));
	i = 0;
	len = 0;
	while (lexeme[i])
	{
		if (lexeme[i] == '\\')
			i++;
		temp[len++] = lexeme[i++];
	}
	free(lexeme);
	return (temp);
}

static void	join_lexemes(t_tokens *tokens)
{
	char		*s;
	t_toklist	*curr;
	t_toklist	*prev;

	prev = tokens->head;
	curr = tokens->head;
	while (curr)
	{
		if (curr->type == BACK_SLASH && curr->next)
		{
			s = ft_strjoin(curr->lexeme + 1, curr->next->lexeme);
			if (!s)
				return ;
			free(curr->next->lexeme);
			curr->next->lexeme = s;
			prev->next = curr->next;
			curr->next = NULL;
			free(curr->lexeme);
			free(curr);
			curr = prev->next;
			tokens->size--;
			tokens->lexeme_count--;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	remove_escape_char(t_tokens *tokens)
{
	char		*s;
	t_toklist	*curr;
	char		*lexeme;

	join_lexemes(tokens);
	s = NULL;
	curr = tokens->head;
	while (curr)
	{
		s = ft_strchr(curr->lexeme, '\\');
		if (s)
		{
			lexeme = rm_backslash(curr->lexeme);
			curr->lexeme = lexeme;
			s = NULL;
		}
		curr = curr->next;
	}
}
