/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/18 17:49:06 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

static void	check_dquotes(t_tokens *tokens)
{
	char	*s;

	s = tokens->user_input;
	while (*s)
	{
		if (*s == '"' && !tokens->is_inside_quote)
		{
			s++;
			tokens->is_inside_quote = true;
			continue ;
		}
		if (*s == '"' && tokens->is_inside_quote)
		{
			s++;
			tokens->is_inside_quote = false;
			continue ;
		}
		if (!*(s + 1) && tokens->is_inside_quote)
			handle_quoting(tokens, D_QUOTE, s - tokens->user_input, &s);
		s++;
	}
}

static void	check_squotes(t_tokens *tokens)
{
	char	*s;

	s = tokens->user_input;
	while (*s)
	{
		if (*s == '\'' && !tokens->is_inside_quote)
		{
			s++;
			tokens->is_inside_quote = true;
			continue ;
		}
		if (*s == '\'' && tokens->is_inside_quote)
		{
			s++;
			tokens->is_inside_quote = false;
			continue ;
		}
		if (!*(s + 1) && tokens->is_inside_quote)
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
	check_dquotes(tokens);
	check_squotes(tokens);
}

char	*prompt1(t_tokens *tokens)
{
	char	*more_input;
	char	*temp;
	char	*temp1;
	int		len;

	more_input = readline("> ");
	if (!more_input)
		return (NULL);
	len = ft_strlen(tokens->user_input);
	temp = (char *)malloc (len + 2);
	if (!temp)
	{
		free(more_input);
		return (NULL);
	}
	ft_strlcpy(temp, tokens->user_input, len + 2);
	temp[len + 1] = '\n';
	temp[len + 2] = '\0';
	temp1 = tokens->user_input;
	tokens->user_input = ft_strjoin(temp, more_input);
	free(temp1);
	free(more_input);
	return (tokens->user_input);
}

int	main(int argc, char **argv, char **env)
{
	t_tokens	tokens;

	(void)argv;
	(void)argc;
	(void)env;
	init_tokens(&tokens);
	while (1)
	{
		prompt(&tokens);
		if (!tokens.user_input)
			break ;
		parse_line(&tokens);
		ft_printf("%s\n", tokens.user_input);
	}
	return (0);
}
