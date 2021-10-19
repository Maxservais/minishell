#include "../minishell.h"

int	occ_in_commands(char **commands, char c)
{
	int	counter;
		int	x;
	int	y;

	counter = 0;
	x = 0;
	x = 0;
	while (commands[x])
	{
		while (commands[x][y])
		{
			if (commands[x][y] == c)
				counter++;
			y++;
		}
		y = 0; 
		x++;
	}
	return (counter);
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
	printf("last == %s\n", commands[num - 1]);
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
		occurences = count_occurence(commands[x], '\"') + count_occurence(commands[x], '\'');
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

void	echo(char **splited, int word_count, int quote)
{
	int		x;

	if (!ft_strncmp(splited[0], "echo", 4) && !splited[1])
		printf("\n");
	else if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
	{
		x = 1;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s\n", splited[x]);
		if (quote)
			printf("\n");
	}
	else if (!ft_strncmp(splited[0], "echo", 4) && !ft_strncmp(splited[1], "-n", 2))
	{
		x = 2;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s", splited[x]);
		if (quote)
			printf("\n");
	}
}
