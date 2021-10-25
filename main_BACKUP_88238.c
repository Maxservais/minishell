#include "minishell.h"

void	handle_command(t_lst *commands)
{
<<<<<<< HEAD
	char	**splited;
	int		word_count;
	int		x;

	splited = ft_split(command, ' ');
	// to be protected
	word_count = 0;
	while (splited[word_count])
		word_count++;
	// Ici au lieu de rentrer dans chacune des fonctions une à une, on peut check la valeur de splited[0]
	echo(splited, word_count, quote);
	pwd(splited);
	cd(splited);
	ft_exit(splited, exit);
	env(splited);
	export(splited);
	x = 0;
	while (splited[x])
		free(splited[x++]);
	free(splited);
=======
	while (commands)
	{
		ft_exit(*commands);
		echo(commands);
		if (!commands->job_done)
			printf("bash: %s: command not found\n", commands->content[0]);
		commands = commands->next;
	}
>>>>>>> parsing
}

void	parser_lst(char *line)
{
	t_lst	*commands;
	char	**splited;
	char	*temp;
	int		x;
	int		y;

	data.nb_of_commands = 0;
	splited = ft_split(line, '|');
	x = 0;
	while (splited[x])
	{
		data.nb_of_commands++;
		temp = ft_strtrim(splited[x], " ");
		free(splited[x]);
		splited[x++] = temp;
	}
	x = 0;
	commands = lstnew(ft_split(splited[x], ' '), x + 1);
	x++;
	while (splited[x])
	{
		lstadd_back(&commands, lstnew(ft_split(splited[x], ' '), x + 1));
		x++;
	}
	y = 0;
	while (splited[y])
		free(splited[y++]);
	free(splited);
	handle_command(commands);
	lstclear(&commands);
}

void	sighandler(int signum)
{
	// printf("signum == %d\n", signum);
	if (signum == 2)
	{
		data.new_line = 1;
		return ;
	}
}

int	main(void)
 {
	char	*line;
	char	first_quote;

	data.exit = -1;
	while (data.exit == -1)
	{
		data.nb_of_commands = 0;
		line = readline("bash-3.2$ ");
		signal(SIGINT, sighandler);
		if (data.new_line)
			line = readline("bash-3.2$ ");
		if (ft_strlen(line))
		{
			first_quote = find_first_quote(line);
			while (count_occurence(line, first_quote) % 2 == 1)
				line = dquote(line);
			line = remove_useless_quotes(line, first_quote);
			parser_lst(line);
		}
		free(line);
	}
	system("leaks minishell");
	return (EXIT_SUCCESS);
}
