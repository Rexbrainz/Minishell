/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndziadzi <ndziadzi@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:06:20 by ndziadzi          #+#    #+#             */
/*   Updated: 2025/02/13 12:11:40 by ndziadzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	cc;

	cc = 0;
	while (s1[cc] != '\0' && s2[cc] != '\0')
	{
		if (s1[cc] != s2[cc])
			return (s1[cc] - s2[cc]);
		cc++;
	}
	return (s1[cc] - s2[cc]);
}
