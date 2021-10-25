#include "../minishell.h"

char	find_first_quote(char *line)
{
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'')
			return ('\'');
		if (line[x] == '\"')
			return ('\"');
		x++;
	}
	return (0);
}

char	*dquote(char *line)
{
	char	*new_line;
	char	*temp;
	char	*temp_2;

	new_line = readline("> ");
	temp_2 = ft_strjoin(line, "\n");
	temp = ft_strjoin(temp_2, new_line);
	free(temp_2);
	free(line);
	free(new_line);
	return (temp);
}

char	*remove_useless_quotes(char *line, char first_quote)
{
	char	*new_line;
	int		x;
	int		y;

	x = 0;
	y = 0;
	new_line = malloc(ft_strlen(line) - count_occurence(line, first_quote) + 1);
	while (line[x])
	{
		if (line[x] == first_quote)
			x++;
		else
			new_line[y++] = line[x++];
	}
	new_line[y] = '\0';
	free(line);
	return (new_line);
}

int	count_occurence(char *str, char c)
{
	int counter;
	int	x;

	x = 0;
	counter = 0;
	while (str[x])
	{
		if (str[x] == c)
			counter++;
		x++;
	}
	return (counter);
}

void	echo(t_lst *command)
{
	int	x;

	if (command->index < data.nb_of_commands)
		return ;
	if (!ft_strncmp(command->content[0], "echo", 4) && !command->content[1])
	{
		printf("\n");
		command->job_done = 1;
	}
	else if (!ft_strncmp(command->content[0], "echo", 4) && ft_strncmp(command->content[1], "-n", 2))
	{
		x = 1;
		while (command->content[x])
		{
			if (command->content[x + 1])
				printf("%s ", command->content[x++]);
			else
				printf("%s", command->content[x++]);
		}
		printf("\n");
		command->job_done = 1;
	}
	else if (!ft_strncmp(command->content[0], "echo", 4) && !ft_strncmp(command->content[1], "-n", 2))
	{
		x = 2;
		while (command->content[x])
		{
			if (command->content[x + 1])
				printf("%s ", command->content[x++]);
			else
				printf("%s", command->content[x++]);
		}
		command->job_done = 1;
	}
}
