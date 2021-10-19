
#include "minishell.h"

int	count_occurence(char *str)
{
	int	x;
	int counter;

	x = 0;
	counter = 0;
	while (str[x])
	{
		if (str[x] == '"' || str[x] == '\'')
			counter++;
		x++;
	}
	return (counter);
}

char	**handle_dquote(char *line, char **commands)
{
	int		num;
	char	*temp;

	num = 0;
	while (commands[num])
		num++;
	temp = ft_strjoin(commands[num - 1], line);
	// to be protected
	free(commands[num - 1]);
	free(line);
	commands[num - 1] = temp;
	return (commands);
}

char	**quote_remover(char **commands)
{
	int		x;
	int		y;
	int		z;
	int		occurences;
	char	*temp;

	x = 0;
	y = 0;
	z = 0;
	while (commands[x])
	{
		occurences = count_occurence(commands[x]);
		temp = malloc(ft_strlen(commands[x]) - occurences + 1);
		// to be protected
		while (commands[x][y])
		{
			if (commands[x][y] != '\'' && commands[x][y] != '\"')
			{
				temp[z] = commands[x][y];
				z++;
			}
			y++;
		}
		temp[z] = '\0';
		free(commands[x]);
		commands[x] = temp;
		z = 0;
		y = 0;
		x++;
	}
	return (commands);
}

void	handle_command(char *command, int *exit)
{
	char	**splited;
	int		word_count;
	int		x;

	splited = ft_split(command, ' ');
	// to be protected
	word_count = 0;
	while (splited[word_count])
		word_count++;
	echo(splited, word_count);
	pwd(splited);
	ft_exit(splited, exit);
	env(splited);
	export(splited);
	x = 0;
	while (splited[x])
		free(splited[x++]);
	free(splited);
}

void	parser(char *line, int *exit)
{
	char	**commands;
	int		x;

	x = 0;
	commands = ft_split(line, '|');
	// to be protected
	if (count_occurence(line) % 2 == 1)
	{
		line = readline(">");
		commands = handle_dquote(line, commands);
	}
	commands = quote_remover(commands);
	// to be protected
	while (commands[x])
	{
		handle_command(commands[x], exit);
		x++;
	}
	x = 0;
	while (commands[x])
		free(commands[x++]);
	free(commands);
}

int	main()
 {
	char	*line;
	int 	exit;

	exit = 0;
	while (!exit)
	{
		line = readline("$");
		parser(line, &exit);
		free(line);
	}
	system("leaks minishell");
	return (EXIT_SUCCESS);
}
