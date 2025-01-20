/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/20 14:25:01 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

static void	quoting_state(t_tokens *tokens)
{
	char	*s;

	s = tokens->user_input;
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
			handle_quoting(tokens, D_QUOTE, s - tokens->user_input, &s);
		if (!*(s + 1) && tokens->is_inside_squote)
			handle_quoting(tokens, S_QUOTE, s - tokens->user_input, &s);
		s++;
	}
}

static void	prompt(t_tokens *tokens)
{
	char	*back_slash;

	tokens->user_input = readline("minishell$ ");
	if (!tokens->user_input)
		return ;
	back_slash = NULL;
	back_slash = ft_strrchr(tokens->user_input, '\\');
	while (back_slash && !*(back_slash + 1))
	{
		tokens->user_input = prompt1(tokens);
		if (!tokens->user_input)
			return ;
		back_slash = ft_strrchr(tokens->user_input, '\\');
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
	len = ft_strlen(tokens->user_input);
	temp = (char *)malloc (len + 1);
	if (!temp)
	{
		free(more_input);
		return (NULL);
	}
	ft_strlcpy(temp, tokens->user_input, len + 1);
	temp[len] = '\n';
	temp[len + 1] = '\0';
	tokens->user_input = ft_strjoin(temp, more_input);
	free(more_input);
	free(temp);
	return (tokens->user_input);
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
		if (!tokens.user_input)
			break ;
		add_history(tokens.user_input);
		parse_line(&tokens);
		ft_printf("USER_INPUT-> [%s]\tLexeme count-> [%d]\n",
			tokens.user_input, tokens.lexeme_count);
		while (tokens.head)
		{
			ft_printf("lexeme-> [%s]\ttype-> [%d]\tPos-> [%d]\t",
				tokens.head->lexeme);
			curr = tokens.head;
			tokens.head = tokens.head->next;
			free(curr);
		}
	}
	return (0);
}
