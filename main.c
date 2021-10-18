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

void	echo(char **splited, int word_count)
{
	int		x;

	if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
	{
		x = 1;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s\n", splited[x]);
	}
	if (!ft_strncmp(splited[0], "echo", 4) && !ft_strncmp(splited[1], "-n", 2))
	{
		x = 2;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s", splited[x]);
	}
}

void	ft_exit(char **splited, int *exit)
{
	if (!ft_strncmp(splited[0], "exit", 5))
		*exit = 1;
}

void pwd(char **splited)
{
	char *pwd;

	if (!ft_strncmp(splited[0], "pwd", 3))
		printf("%s\n", getcwd(pwd, 50));
}

void	handle_command(char *command, int *exit)
{
	char	**splited;
	int		word_count;
	int		x;

	splited = ft_split(command, ' ');
	word_count = 0;
	while (splited[word_count])
		word_count++;
	echo(splited, word_count);
	pwd(splited);
	ft_exit(splited, exit);
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
		handle_command(commands[x], exit);
		x++;
	}
	x = 0;
	while (commands[x])
		free(commands[x++]);
	free(commands);
}

int end(char *line)
{
	free(line);
	// system("leaks a.out");
	return (0);
}

int	main()
 {
	char	*line;
	int 	exit;

	exit = 0;
	while (!exit)
	{
		line = readline("mini_shell>");
		parser(line, &exit);
	}
	return (end(line));
}