/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 14:51:15 by mservais          #+#    #+#             */
/*   Updated: 2021/06/04 15:44:45 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*final_list;

	if (!lst)
		return (NULL);
	final_list = NULL;
	while (lst != NULL && f != NULL)
	{
		node = ft_lstnew((*f)(lst->content));
		if (!node)
		{
			ft_lstclear(&final_list, del);
			return (NULL);
		}
		ft_lstadd_back(&final_list, node);
		lst = lst->next;
	}
	return (final_list);
}
