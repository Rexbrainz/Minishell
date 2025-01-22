/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/22 13:03:44 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"
/*
static void	check_last_char(t_tokens *tokens)
{
	int		i;
	char	*p;
	char	*r_paren;
	char	*lc;

	i = 0;
	while (true)
	{
		lc = &tokens->t_input[ft_strlen(tokens->t_input)];
		p = lc - 1;
		if (*p == '\\')
			return ;
		else if ((*p == '|' && *lc == '|') || (*p == '&' && *lc == '&')
			|| *lc == '|' || *lc == '\\')
			prompt1(tokens);
		else
			return ;
	}
}
*/

static void	quoting_state(t_tokens *tokens)
{
	char	*s;

	s = tokens->t_input;
	while (*s)
	{
		if (*s == '"' && *(s - 1) != '\\' && !tokens->is_inside_dquote
			&& !tokens->is_inside_squote)
			tokens->is_inside_dquote = true;
		else if (*s == '"' && *(s - 1) != '\\' && tokens->is_inside_dquote)
			tokens->is_inside_dquote = false;
		if (*s == '\'' && !tokens->is_inside_squote
			&& !tokens->is_inside_dquote)
			tokens->is_inside_squote = true;
		else if (*s == '\'' && tokens->is_inside_squote)
			tokens->is_inside_squote = false;
		if (!*(s + 1) && tokens->is_inside_dquote)
			handle_quoting(tokens, D_QUOTE, s - tokens->t_input, &s);
		if (!*(s + 1) && tokens->is_inside_squote)
			handle_quoting(tokens, S_QUOTE, s - tokens->t_input, &s);
		s++;
	}
}

static void	prompt(t_tokens *tokens)
{
	char	*back_slash;

	tokens->t_input = readline("minishell$ ");
	if (!tokens->t_input)
		return ;
	back_slash = NULL;
	back_slash = ft_strrchr(tokens->t_input, '\\');
	while (back_slash && !*(back_slash + 1))
	{
		tokens->t_input = prompt1(tokens);
		if (!tokens->t_input)
			return ;
		back_slash = ft_strrchr(tokens->t_input, '\\');
	}
	quoting_state(tokens);
}

char	*prompt1(t_tokens *tokens)
{
	char	*more_input;
	char	*temp;
	int		len;

	more_input = readline("> ");
	if (!more_input)
		return (NULL);
	len = ft_strlen(tokens->t_input);
	temp = (char *)malloc (len + 1);
	if (!temp)
	{
		free(more_input);
		return (NULL);
	}
	ft_strlcpy(temp, tokens->t_input, len + 1);
	temp[len] = '\n';
	temp[len + 1] = '\0';
	free(tokens->t_input);
	tokens->t_input = ft_strjoin(temp, more_input);
	free(more_input);
	free(temp);
	return (tokens->t_input);
}

int	main(int argc, char **argv, char **env)
{
	t_tokens	tokens;
	t_toklist	*curr;

	(void)argv;
	(void)argc;
	(void)env;
	init_tokens(&tokens);
	while (1)
	{
		prompt(&tokens);
		if (!tokens.t_input)
			break ;
		add_history(tokens.t_input);
		parse_line(&tokens);
		ft_printf("t_input-> [%s]\tLexeme count-> [%d]\n\n",
			tokens.t_input, tokens.lexeme_count);
		while (tokens.head)
		{
			ft_printf("lexeme-> [%s]\ttype-> [%d]\tPos-> [%d]\t\n",
				tokens.head->lexeme, tokens.head->type, tokens.head->start_pos);
			curr = tokens.head;
			tokens.head = tokens.head->next;
			free(curr->lexeme);
			free(curr);
		}
		free(tokens.t_input);
	}
	return (0);
}
