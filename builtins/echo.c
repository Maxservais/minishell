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

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

// void	echo(char **splited, int quote, int new_lines)
// {
// 	int		x;
// 	int		y;

// 	int z = 0;
// 	while (splited[z])
// 	{
// 		printf("result == %s\n", splited[z]);
// 		z++;
// 	}
// 	y = 0;
// 	if (!ft_strncmp(splited[0], "echo", 4) && !splited[1])
// 		printf("\n");
// 	else if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
// 	{
// 		x = 1;
// 		while (splited[x])
// 		{
// 			while (splited[x][y + quote])
// 			{
// 				if (y == (int)ft_strlen(splited[x]) - 1 && !(is_quote(splited[x][y])))
// 					printf("%c ", splited[x][y++]);
// 				else if (is_quote(splited[x][y]))
// 					y++;
// 				else
// 					printf("%c", splited[x][y++]);
// 			}
// 			if (quote)
// 				printf("\n");
// 			while (splited[x][y])
// 			{
// 				if (is_quote(splited[x][y]))
// 					y++;
// 				else
// 					printf("%c", splited[x][y++]);
// 			}
// 			x++;
// 			y = 0;
// 		}
// 		printf("\n");
// 	}
// 	else if (!ft_strncmp(splited[0], "echo", 4) && !ft_strncmp(splited[1], "-n", 2))
// 	{
// 		x = 2;
// 		while (splited[x])
// 		{
// 			while (splited[x][y + quote])
// 			{
// 				if (is_quote(splited[x][y]))
// 					y++;
// 				else
// 					printf("%c", splited[x][y++]);
// 			}
// 			if (splited[x + 1])
// 				printf(" ");
// 			if (quote)
// 				printf("\n");
// 			while (splited[x][y])
// 			{
// 				if (is_quote(splited[x][y]))
// 					y++;
// 				else
// 					printf("%c", splited[x][y++]);
// 			}
// 			x++;
// 			y = 0;
// 		}
// }
// 	if (new_lines)
// 		printf("\n");
// 	}
