#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include "libft/libft.h"
#include "pipex.h"

void	handle_command(char *command, int *exit, int quote)
{
	char	**splited;
	int		word_count;
	int		x;

	splited = ft_split(command, ' ');
	// to be protected
	word_count = 0;
	while (splited[word_count])
		word_count++;
	echo(splited, word_count, quote);
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
	int		quote;

	x = 0;
	commands = ft_split(line, '|');
	// to be protected
	quote = 0;
	while (occ_in_commands(commands, '\'') % 2 == 1
		|| occ_in_commands(commands, '\"') % 2 == 1)
	{
		quote = 1;
		line = readline(">");
		commands = handle_dquote(line, commands);
	}
	commands = quote_remover(commands);
	// to be protected
	while (commands[x])
	{
		handle_command(commands[x], exit, quote);
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
		line = readline("sh-3.2$");
		parser(line, &exit);
		free(line);
	}
	// system("leaks a.out");
	return (0);
}
