/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:18:57 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/15 11:58:32 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

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
	while (1)
	{
		if (!prompt())
			break ;
	}
	return (0);
}
