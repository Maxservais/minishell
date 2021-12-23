#include "../minishell.h"

int	lstsize(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_lst	*lstnew(char **content, int index)
{
	t_lst	*node;

	node = malloc(sizeof(t_lst));
	if (!node)
		return (NULL);
	(*node).prev = NULL;
	(*node).content = content;
	(*node).type = 0;
	(*node).index = index;
	(*node).next = NULL;
	return (node);
}

t_lst	*lstlast(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_lst **lst, t_lst *new)
{
	if (!lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lstlast(*lst)->next = new;
	lstlast(*lst)->prev = *lst;
}

void	lstclear(t_lst **lst)
{
	t_lst	*trav;

	if (!lst || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		trav = *lst;
		*lst = (*lst)->next;
		lstdelone(trav);
	}
	*lst = NULL;
}
