#include "../../minishell.h"

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

int	echo(t_lst *command)
{
	int	x;

	// if (command->index < data.nb_of_commands)
	// 	return ;
	if (!ft_strncmp(command->content[0], "echo", 4) && !command->content[1])
	{
		write(1, "\n", 1);
		command->job_done = 1;
		return (0);
	}
	else if (!ft_strncmp(command->content[0], "echo", 4) && ft_strncmp(command->content[1], "-n", 2))
	{
		x = 1;
		while (command->content[x])
		{
			if (!ft_strncmp(command->content[x], "$?", 2))
			{
				ft_putnbr(data.command_code);
				x++;
			}
			else if (command->content[x + 1])
			{
				write(1, command->content[x], ft_strlen(command->content[x]));
				write(1, " ", 1);
				x++;
			}
			else
			{
				write(1, command->content[x], ft_strlen(command->content[x]));
				x++;
			}
			write(1, " ", 1);
		}
		write(1, "\n", 1);

		command->job_done = 1;
		return (0);
	}
	else if (!ft_strncmp(command->content[0], "echo", 4) && !ft_strncmp(command->content[1], "-n", 2))
	{
		x = 2;
		while (command->content[x])
		{
			if (command->content[x + 1])
			{
				write(1, command->content[x], ft_strlen(command->content[x]));
				write(1, " ", 1);
				x++;
			}
			else
			{
				write(1, command->content[x], ft_strlen(command->content[x]));
				x++;
			}
		}
		command->job_done = 1;
		return (0);
	}
	return (1);
}
