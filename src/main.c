/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/16 17:29:44 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parser.h"

static char	*prompt(void)
{
	char	*line;

	ft_printf("minishell$ ");
	return (readline(line));
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
