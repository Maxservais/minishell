#include "../minishell.h"

int	last_infile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->infile[x + 1].name)
		x++;
	return (x);
}

int	last_outfile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->outfile[x + 1].name)
		x++;
	return (x);
}

void	add_index(t_lst **commands)
{
	int		index;
	t_lst	*trav;
	int		x;

	index = 1;
	trav = *commands;
	while (trav)
	{
		x = 0;
		trav->args = 0;
		// printf("coucoucoucou\n");
		// printf("trav->content[x]: %s\n", trav->content[0]);
		while (trav->content[x++])
		{
			trav->args++;
		}
		trav->index = index++;
		trav = trav->next;
	}
}

char	*add_env(char *line)
{
	int			x;
	int			dollar;
	int			space;
	char		*key;
	char		*string_before;
	char		*string_after;
	char		*value;
	char		*temp;
	char		*new_line;

	x = 0;
	value = NULL;
	dollar = char_position(line, '$');
	space = space_position(line, ' ', dollar);
	if (dollar >= 0)
	{
		key = ft_substr(line, dollar + 1, space - dollar);
		string_before = ft_substr(line, 0, dollar);
		string_after = ft_substr(line, space, ft_strlen(line));
		while (data.envp[x])
		{
			if (!ft_strncmp(data.envp[x], key, ft_strlen(key) - 1))
			{
				value = ft_substr(data.envp[x], ft_strlen(key) + 1, ft_strlen(data.envp[x]) - 1);
				break ;
			}
			x++;
		}
		temp = ft_strjoin(string_before, value);
		free(value);
		free(string_before);
		new_line = ft_strjoin(temp, string_after);
		free(string_after);
		free(temp);
		free(key);
		free(line);
		return (new_line);
	}
	return (line);
}
