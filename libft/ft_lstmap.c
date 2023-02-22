/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rertzer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 10:13:07 by rertzer           #+#    #+#             */
/*   Updated: 2022/11/13 14:42:11 by rertzer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstdest;
	t_list	*current;

	lstdest = NULL;
	if (lst)
	{
		lstdest = ft_lstnew(f(lst->content));
		current = lstdest;
		lst = lst->next;
	}
	while (lst)
	{
		current->next = ft_lstnew(f(lst->content));
		if (current->next == NULL)
		{
			ft_lstclear(&lstdest, del);
			return (NULL);
		}
		current = current->next;
		lst = lst->next;
	}
	return (lstdest);
}
