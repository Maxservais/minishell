#include "minishell.h"

int		execute_builtin(t_lst *commands)
{
	if (!ft_strncmp(commands->content[0], "cd", 2))
		cd(commands);
	else if (!ft_strncmp(commands->content[0], "echo", 4))
		echo(commands);
	else if (!ft_strncmp(commands->content[0], "env", 3))
		env(commands);
	else if (!ft_strncmp(commands->content[0], "exit", 5))
		ft_exit(commands);
	else if (!ft_strncmp(commands->content[0], "export", 6))
		export(commands);
	else if (!ft_strncmp(commands->content[0], "pwd", 3))
		pwd(commands);
	// Return Success if at least one builtin command got executed
	return (0);
}

void	handle_command(t_lst *commands)
{
	while (commands)
	{
		execute_builtin(commands);
		// execute_external_cmd(commands);
		// execute pipe
		// execute redirection
		// ...
		if (!commands->job_done)
		{
			printf("bash: %s: command not found\n", commands->content[0]);
			data.command_code = 127;
		}
		commands = commands->next;
	}
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
