/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/15 18:05:47 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parse.h"

static char	*prompt(void)
{
	char	*line;

	ft_printf("minishell$ ");
	return (readline(line));
}

int	main(int argc, char **argv, char **env)
{
	char		*line;
	t_toklist	*tokens;

	(void)argv;
	(void)argc;
	(void)env;
	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		tokens = parse_line(line);
		ft_printf("%s\n", line);
	}
	return (0);
}
