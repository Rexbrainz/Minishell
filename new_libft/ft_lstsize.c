/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sudaniel <sudaniel@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 07:31:59 by sudaniel          #+#    #+#             */
/*   Updated: 2024/10/12 07:46:05 by sudaniel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
int main(void)
{
	int value = 42, value1 = 124, count = 5;
	t_list *list = ft_lstnew(&value);
	t_list *new_node = ft_lstnew(&value1);
	ft_lstadd_front(&list, new_node);
	while (count--)
	{
		new_node = ft_lstnew(&count);
		ft_lstadd_front(&list, new_node);
	}
	printf("There are %d numbers of nodes in the list.\n", ft_lstsize(list));
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}
	return (0);
}
*/
