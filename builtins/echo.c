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

char	**handle_dquote(char *line, char **commands, int *quote)
{
	int		num;
	char	*temp;
	int 	first_len;
	int 	last_len;

	num = 0;
	while (commands[num])
		num++;
	first_len = ft_strlen(commands[num - 1]);
	temp = ft_strjoin(commands[num - 1], line);
	last_len = ft_strlen(temp);
	*quote += last_len - first_len;
	// to be protected
	free(commands[num - 1]);
	free(line);
	commands[num - 1] = temp;
	return (commands);
}

char	**quote_remover(char **commands, char first_quote)
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
			if (commands[x][y] != first_quote)
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
	int		y;

	word_count++;
	y = 0;
	if (!ft_strncmp(splited[0], "echo", 4) && !splited[1])
		printf("\n");
	else if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
	{
		x = 1;
		while (splited[x])
		{
			while (splited[x][y + quote])
			{
				if (y == (int)ft_strlen(splited[x]) - 1 && !(splited[x][y] == '\'' || splited[x][y] == '\"'))
					printf("%c ", splited[x][y++]);
				else if (splited[x][y] == '\'' || splited[x][y] == '\"')
					y++;
				else
					printf("%c", splited[x][y++]);
			}
			if (quote)
				printf("\n");
			while (splited[x][y])
			{
				if (splited[x][y] == '\'' || splited[x][y] == '\"')
					y++;
				else
					printf("%c", splited[x][y++]);
			}
			x++;
			y = 0;
		}
		printf("\n");
	}
	else if (!ft_strncmp(splited[0], "echo", 4) && !ft_strncmp(splited[1], "-n", 2))
	{
		x = 2;
		while (splited[x][y + quote])
		{
			if (splited[x][y] == '\'' || splited[x][y] == '\"')
				y++;
			else
				printf("%c", splited[x][y++]);
		}
		if (quote)
			printf("\n");
		while (splited[x][y])
		{
			if (splited[x][y] == '\'' || splited[x][y] == '\"')
				y++;
			else
				printf("%c", splited[x][y++]);
		}
	}
}

// void	echo(char **splited, int word_count, int quote)
// {
// 	int		x;
// 	int		y;

// 	y = 0;
// 	if (!ft_strncmp(splited[0], "echo", 4) && !splited[1])
// 		printf("\n");
// 	else if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
// 	{
// 		x = 1;
// 		while (splited[x] && x != word_count - 1)
// 			printf("%s ", splited[x++]);
// 		if (!quote)
// 			printf("%s ", splited[x]);
// 		while (splited[x][y + quote - 1])
// 		{
// 			printf("%c", splited[x][y]);
// 			y++;
// 		}
// 		while (quote && splited[x][y])
// 		{
// 			if (splited[x][y] == '\'' || splited[x][y] == '\"')
// 				printf("\n%c", splited[x][y]);
// 			else
// 				printf("%c", splited[x][y]);
// 			y++;
// 		}
// 		printf("\n");
// 		if (quote)
// 			printf("\n");
// 	}
// 	else if (!ft_strncmp(splited[0], "echo", 4) && !ft_strncmp(splited[1], "-n", 2))
// 	{
// 		x = 2;
// 		while (splited[x] && x != word_count - 1)
// 			printf("%s ", splited[x++]);
// 		if (!quote)
// 			printf("%s", splited[x]);
// 		while (splited[x][y + quote - 1])
// 		{
// 			printf("%c", splited[x][y]);
// 			y++;
// 		}
// 		while (quote && splited[x][y])
// 		{
// 			printf("\n");
// 			printf("%c", splited[x][y]);
// 			y++;
// 		}
// 		if (quote)
// 			printf("\n");
// 	}
// }

