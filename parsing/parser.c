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
	commands = lstnew(split_token(splited[x]), x + 1);
	x++;
	while (splited[x])
	{
		lstadd_back(&commands, lstnew(split_token(splited[x]), x + 1));
		data.nb_of_commands++;
		x++;
	}
	add_index(&commands);
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
		while (trav->content[x] && !strncmp(trav->content[x], ">>", 2))
		{
			if (!trav->content[x][2])
				x += 2;
			else
				x++;
		}
		while (trav->content[x] && trav->content[x][0] == '<')
		{
			if (!trav->content[x][1])
				x += 2;
			else
				x++;
		}
		while (trav->content[x] && trav->content[x][0] == '>')
		{
			if (!trav->content[x][1])
				x += 2;
			else
				x++;
		}
		while (trav->content[x] && trav->content[x][0] != '<' && trav->content[x][0] != '>' && strncmp(trav->content[x], ">>", 2))
			trav->cmd[y++] = ft_strdup(trav->content[x++]);;
		trav->cmd[y] = NULL;
		trav = trav->next;
	}
}
