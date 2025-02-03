/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:26:26 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 08:51:46 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*previous;
	t_list	*current;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	previous = NULL;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	previous->next = new;
}
/*
int main(void)
{
	int data = 32, data1 = 56;
	t_list *list = ft_lstnew(&data);
	t_list *new_node = ft_lstnew(&data1);
	ft_lstadd_back(&list, new_node);
	t_list *temp = list;
	while (temp)
	{
		if (temp->next == NULL)
			printf("The data in the last node: %d\n", *(int *)temp->content);
		temp = temp->next;
	}
	while (list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
	return (0);
}
*/
