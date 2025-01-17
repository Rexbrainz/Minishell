/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 13:04:37 by sudaniel          #+#    #+#             */
/*   Updated: 2025/01/17 19:16:04 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../Includes/minishell.h"

int	get_rest_of_lexeme(char **c)
{
	char	*s;

	s = *c;
	while (ft_isspace(**c))
		(*c)++;
	while (**c && **c != ' ')
		(*c)++;
	return (*c - s);
}

char	*manage_before_prompt1(char **c)
{
	char	*s;
	int		len;

	len = ft_strlen(*c);
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	ft_strlcpy(s, *c, len + 1);
	return (s);
}
