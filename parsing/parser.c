#include "../minishell.h"

t_lst	*put_in_list(char **splited)
{
	t_lst	*commands;
	int		x;
	char	*temp;

	x = 0;
	g_data.nb_of_commands = 1;
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
		g_data.nb_of_commands++;
		x++;
	}
	add_index(&commands);
	return (commands);
}

int	syntax_error(void)
{
	printf("bash: syntax error near unexpected token `newline'\n");
	return (-1);
}

int	check_syntax(t_lst *commands)
{
	int		x;
	t_lst	*trav;

	x = 0;
	trav = commands;
	if (trav->content[x] && !ft_strcmp(trav->content[x], ">>"))
	{
		if (!trav->content[x + 1] || !trav->content[x + 2])
			return (syntax_error());
	}
	else if (trav->content[x] && !ft_strncmp(trav->content[x], ">", 1))
	{
		if (!trav->content[x + 1] || !trav->content[x + 2])
			return (syntax_error());
	}
	else if (trav->content[x] && !ft_strncmp(trav->content[x], "<", 1))
	{
		if (!trav->content[x + 1] || !trav->content[x + 2])
			return (syntax_error());
	}
	return (0);
}

int	check_chevron(t_lst *comd, int x, int y)
{
	while (comd->content[x] && !ft_strncmp(comd->content[x], ">>", 2))
	{
		if (!comd->content[x][2])
			x += 2;
		else
			x++;
	}
	while (comd->content[x] && comd->content[x][0] == '<')
	{
		if (!comd->content[x][1])
			x += 2;
		else
			x++;
	}
	while (comd->content[x] && comd->content[x][0] == '>')
	{
		if (!comd->content[x][1])
			x += 2;
		else
			x++;
	}
	while (comd->content[x] && comd->content[x][0] != '<' &&
		comd->content[x][0] != '>' && ft_strncmp(comd->content[x], ">>", 2))
			comd->cmd[y++] = ft_strdup(comd->content[x++]);
	return (y);
}

void	remove_files(t_lst *commands)
{
	int		x;
	int		y;

	while (commands)
	{
		commands->cmd = malloc(sizeof(char *) * (commands->args + 1));
		if (!commands->cmd)
		{
			printf("Malloc failed\n");
			return ;
		}
		x = 0;
		y = 0;
		y = check_chevron(commands, x, y);
		commands->cmd[y] = NULL;
		commands = commands->next;
	}
}
