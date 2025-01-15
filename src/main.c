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
<<<<<<< HEAD
    char *res;
    printf("TEST Minishell\n");
    int x= 123456;

    res = ft_itoa(x);
    printf("Test Libft: %s\n", res);
    return (0);
=======
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
>>>>>>> f8d83398941d9cb18b6fba54f185b561514e37d5
}
