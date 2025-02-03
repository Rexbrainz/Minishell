/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:50:55 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 08:18:43 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	last = NULL;
	if (!lst)
		last = lst;
	else
	{
		while (lst)
		{
			last = lst;
			lst = lst->next;
		}
	}
	return (last);
}
/*
int main(void)
{
	int content = 42, content1 = 123, content2 = 0;
	t_list *list = ft_lstnew(&content);
	t_list *new_node = ft_lstnew(&content1);
	t_list *add_front = ft_lstnew(&content2);
	ft_lstadd_front(&list, new_node);
	ft_lstadd_front(&list, add_front);
    t_list *last = ft_lstlast(list);
	printf("The content in the last node is: %d\n", *(int *)last->content);
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}	
	return (0);
}
*/
