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
	(*node).job_done = 0;
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

void	lstdelone(t_lst *lst)
{
	int	x;

	if (!lst)
		return ;
	x = 0;
	while (lst->content[x])
		free(lst->content[x++]);
	free(lst->content);
	x = 0;
	while (lst->cmd[x])
		free(lst->cmd[x++]);
	free(lst->cmd);
	free(lst->infile);
	free(lst->outfile);
	free(lst);
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

int	strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *str, char *end)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != end[i])
			return (1);
		i++;
	}
	return (0);
}
