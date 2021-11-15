#include "../minishell.h"

t_lst	*put_in_list(char **splited)
{
	t_lst	*commands;
	int		x;
	char	*temp;

	x = 0;
	data.nb_of_commands = 1;
	while (splited[x])
	{
		temp = ft_strtrim(splited[x], " ");
		free(splited[x]);
		splited[x++] = temp;
	}
	x = 0;
	commands = lstnew(ft_split(splited[x], ' '), x + 1);
	x++;
	while (splited[x])
	{
		lstadd_back(&commands, lstnew(ft_split(splited[x], ' '), x + 1));
		data.nb_of_commands++;
		x++;
	}
	x = 0;
	add_index(&commands);
	while (splited[x])
		free(splited[x++]);
	free(splited);
	return (commands);
}

void	remove_files(t_lst **commands)
{
	t_lst	*trav;
	int		x;
	int		y;

	trav = *commands;
	while (trav)
	{
		trav->cmd = malloc(sizeof(char *) * (trav->args + 1));
		x = 0;
		y = 0;
		while (trav->content[x][0] == '<')
			x += 2;
		while (trav->content[x] && trav->content[x][0] != '<' && trav->content[x][0] != '>')
				trav->cmd[y++] = ft_strdup(trav->content[x++]);
		trav->cmd[y] = NULL;
		trav = trav->next;
	}
}
