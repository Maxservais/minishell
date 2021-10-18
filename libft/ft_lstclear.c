/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:56:15 by mservais          #+#    #+#             */
/*   Updated: 2021/07/06 11:17:22 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*trav;

	if (!lst || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		trav = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(trav, del);
	}
	*lst = NULL;
}
