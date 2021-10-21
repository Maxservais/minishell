#include "minishell.h"

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

void	parser(char *line, int *exit)
{
	char	**commands;
	int		x;
	int		quote;
	char	first_quote;

	x = 0;
	commands = ft_split(line, '|');
	// to be protected
	quote = 0;
	first_quote = find_first_quote(line);
	while (first_quote && occ_in_commands(commands, first_quote) % 2 == 1)
	{
		line = readline("> ");
		commands = handle_dquote(line, commands, &quote);
		printf("%c\n", first_quote);
	}
	// commands = quote_remover(commands, first_quote);
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
		line = readline("bash-3.2$ ");
		parser(line, &exit);
		free(line);
	}
	// system("leaks minishell");
	return (EXIT_SUCCESS);
}
