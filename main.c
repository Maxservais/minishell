#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

int	count_occurence(char *str)
{
	int counter;
	int	x;

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
	int	num;
	char	*temp;

	num = 0;
	while (commands[num])
		num++;
	temp = ft_strjoin(commands[num - 1], line);
	free(commands[num - 1]);
	free(line);
	commands[num - 1] = temp;
	return (commands);
}

// char **clean_commands(char **commands)
// {
// 	int		x;
// 	char	*temp;

// 	x = 0;
// 	while (commands[x])
// 	{
// 		temp = ft_strtrim(commands[x], "'\" ");
// 		free(commands[x]);
// 		commands[x] = temp;
// 		x++;
// 	}
// 	return (commands);
// }

void	handle_command(char *command)
{
	char **splited_command;
	int	x;

	splited_command = ft_split(command, ' ');
	x = 1;
	if (!ft_strncmp(splited_command[0], "echo", 4))
		while (splited_command[x])
			printf("%s ", splited_command[x++]);
	if (!(!ft_strncmp(splited_command[0], "echo", 4) && !ft_strncmp(splited_command[1], "-n", 2)))
		printf("\n");
	x = 0;
	while (splited_command[x])
		free(splited_command[x++]);
	free(splited_command);
}

void	parser(char *line)
{
	char	**commands;
	int		x;

	x = 0;
	commands = ft_split(line, '|');
	if (count_occurence(line) % 2 == 1)
	{
		line = readline("dquote>");
		commands = handle_dquote(line, commands);
	}
	// commands = clean_commands(commands);
	// while (commands[x])
	// {
	// 	printf("%s\n", commands[x]);
	// 	x++;
	// }
	while (commands[x])
	{
		handle_command(commands[x]);
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

	line = readline("mini_shell >");
	parser(line);
	free(line);
	// system("leaks a.out");
	return (0);
}