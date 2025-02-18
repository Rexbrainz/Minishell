/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:39:09 by sudaniel          #+#    #+#             */
/*   Updated: 2025/02/18 12:04:25 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Includes/minishell.h"

/* *************************************************************
 * Takes the tokens list, the current node to be deleted       *
 * the previous node and an address of string s to be joined.  *
 * The prev node's lexeme is updated to the joined string.     *
 * The current node and the next is then deleted.              *
 * The function returns nothing.                               *
 * *************************************************************/
static void	backslash_in_word(t_tokens *tokens, t_toklist *prev,
	t_toklist *curr, char **s)
{
	char	*p;

	p = ft_strjoin(prev->lexeme, *s);
	if (!p)
		return ;
	free(*s);
	free(prev->lexeme);
	free(curr->lexeme);
	free(curr->next->lexeme);
	prev->lexeme = p;
	prev->next = curr->next->next;
	curr->next->next = NULL;
	curr->next = NULL;
	free(curr->next);
	free(curr);
	tokens->lexeme_count -= 2;
}

/* ******************************************************
 * Takes the tokens list and modifies it by deleting    *
 * a node from the list.                                *
 * ******************************************************/
static void	not_in_word(t_tokens *tokens, t_toklist *prev,
	t_toklist *curr, char **s)
{
	free(curr->next->lexeme);
	curr->next->lexeme = *s;
	prev->next = curr->next;
	curr->next = NULL;
	free(curr->lexeme);
	free(curr);
	tokens->lexeme_count--;
}

/* *************************************************************
 * Searches the lexeme passed as argument for backslash char,  *
 * when found it removes it and returns the lexeme without     *
 * the backslash.                                              *
 * *************************************************************/
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

/* *********************************************************************
 * Takes the tokens list, iterates through it insearch of back_slash   *
 * tokens, when found, it joins previous tokens lexeme with the        *
 * character after the backslash character, technically removing the   *
 * backslash character.                                                *
 * It returns nothing.                                                 *
 * *********************************************************************/
static void	join_lexemes(t_tokens *tokens)
{
	char		*s;
	t_toklist	*curr;
	t_toklist	*prev;

	prev = tokens->head;
	curr = tokens->head;
	while (curr)
	{
		if (curr->type == BACK_SLASH && curr->next
			&& curr->next->type != L_BACK_SLASH)
		{
			s = ft_strjoin(curr->lexeme + 1, curr->next->lexeme);
			if (!s)
				return ;
			if (tokens->backslash_inside_word)
				backslash_in_word(tokens, prev, curr, &s);
			else
				not_in_word(tokens, prev, curr, &s);
			curr = prev;
		}
		prev = curr;
		curr = curr->next;
	}
}

/* ***********************************************************
 * Takes the tokens list and goes through all lexemes in     *
 * search of unescaped backslash character.                  *
 * Removes backslash characters in every lexeme when found.  *
 * It returns nothing.                                       *
 * ***********************************************************/
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
		if (curr->type != S_QUOTE)
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
