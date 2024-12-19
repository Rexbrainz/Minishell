/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 06:26:06 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 06:45:41 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = (t_list *) malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
/*
int main(void)
{
	int value = 42;
	t_list	*list = ft_lstnew(&value);

	if (list)
	{
		printf("Node content: %d\n", *(int *)list->content);
		free(list);
	}
	else
		printf("Memory allocation failled\n");
	return (0);
}
*/
