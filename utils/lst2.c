#include "../minishell.h"

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
