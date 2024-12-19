/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 06:49:12 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/13 20:10:54 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int main(void)
{
	t_list *list;
	t_list *new;
	t_list *temp;
	int value = 42;
	int value1 = 124;

	list = ft_lstnew(&value);
	new = ft_lstnew(&value1);
	ft_lstadd_front(&list, new);
	while (list)
	{
		printf("%d\n", *(int *)list->content);
		temp = list;
		list = list->next;
		free(temp);
	}
	return (0);
}
*/
