#include "../minishell.h"

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

int	ft_strisdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *str, char *end)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "(null)", 6) == 0)
		return (0);
	if (ft_strlen(str) != ft_strlen(end))
		return (1);
	while (end[i] != '\0' && str[i] != '\0')
	{
		if (str[i] != end[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp_unset(char *str, char *end)
{
	int	i;

	i = 0;
	printf("str = |%s| end = |%s|\n", str, end);
	while (end[i] != '\0' && str[i] != '\0')
	{
		if (str[i] != end[i])
			return (1);
		i++;
	}
	if (str[i] != '=')
		return (1);
	return (0);
}

int	ft_strcmp_parse(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (1);
	while (i < n && str2[i] != '\0' && str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}
