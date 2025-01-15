/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/15 15:48:15 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "parse.h"

static char	*prompt(void)
{
	char	*user;
	char	*line;

	user = getenv("USER");
	ft_printf("%s$ ", user);
	return (readline(line));
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = prompt();
		if (!line)
			break ;
		parse_line(line);
		ft_printf("%s\n", line);
	}
	return (0);
}
