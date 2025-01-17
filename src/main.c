/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 19:15:31 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

static char	*prompt(void)
{
	char	*line;
	int		len;

	ft_printf("minishell$ ");
	return (readline(line));
}

char	*prompt2(t_tokens *tokens)
{
	char	*more_input;
	char	*temp;
	char	*temp1;
	int		len;

	ft_printf("> ");
	more_input = readline(more_input);
	if (!more_input)
		return (NULL);
	len = ft_strlen(tokens->user_input);
	temp = (char *)malloc (len + 2);
	if (!temp)
		return (NULL);
	ft_strlcpy(temp, tokens->user_input, len + 2);
	len = 0;
	while (temp[len])
		len++;
	temp[len] = '\n';
	temp[len + 1] = '\0';
	temp1 = tokens->user_input;
	tokens->user_input = ft_strjoin(temp, more_input);
	free(temp1);
	return (tokens->user_input);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_tokens	tokens;

	(void)argv;
	(void)argc;
	(void)env;
	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		parse_line(&tokens, line);
		ft_printf("%s\n", line);
	}
	return (0);
}
