#include "minishell.h"

void	echo(t_lst commands)
{
	int	x;

	if (!ft_strncmp(commands.content[0], "echo", 4) && !commands.content[1])
	{
		printf("\n");
		return ;
	}
	else if (!ft_strncmp(commands.content[0], "echo", 4) && ft_strncmp(commands.content[1], "-n", 2))
	{
		x = 1;
		while (commands.content[x])
		{
			if (commands.content[x + 1])
				printf("%s ", commands.content[x++]);
			else
				printf("%s", commands.content[x++]);
		}
		printf("\n");
	}
	else if (!ft_strncmp(commands.content[0], "echo", 4) && !ft_strncmp(commands.content[1], "-n", 2))
	{
		x = 2;
		while (commands.content[x])
		{
			if (commands.content[x + 1])
				printf("%s ", commands.content[x++]);
			else
				printf("%s", commands.content[x++]);
		}
	}
}

void	handle_command(t_lst *commands)
{
	while (commands)
	{
		ft_exit(*commands);
		echo(*commands);
		commands = commands->next;
	}
}

char	find_first_quote(char *line)
{
	int		x;

<<<<<<< HEAD
	splited = ft_split(command, ' ');
	// to be protected
	word_count = 0;
	while (splited[word_count])
		word_count++;
	echo(splited, word_count, quote);
	pwd(splited);
	cd(splited);
	ft_exit(splited, exit);
	env(splited);
	export(splited);
=======
>>>>>>> parsing
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

char	*dquote(char *line)
{
	char	*new_line;
	char	*temp;
	char	*temp_2;

	new_line = readline("> ");
	temp_2 = ft_strjoin(line, "\n");
	temp = ft_strjoin(temp_2, new_line);
	free(temp_2);
	free(line);
	free(new_line);
	return (temp);
}

char	*remove_useless_quotes(char *line, char first_quote)
{
	char	*new_line;
	int		x;
	int		y;

	x = 0;
	y = 0;
	new_line = malloc(ft_strlen(line) - count_occurence(line, first_quote) + 1);
	while (line[x])
	{
		if (line[x] == first_quote)
			x++;
		else
			new_line[y++] = line[x++];
	}
	new_line[y] = '\0';
	free(line);
	return (new_line);
}

int	position_of_char(char *line, char c)
{
	int	position;
	int	x;

	x = 0;
	position = 0;
	while (line[x])
	{
		if (line[x] == c)
			return (x);
		x++;
	}
	return (-1);
}

void	parser_lst(char *line)
{
	t_lst	*commands;
	char	**splited;
	char	*temp;
	int		x;
	int		y;

	splited = ft_split(line, '|');
	x = 0;
	while (splited[x])
	{
		temp = ft_strtrim(splited[x], " ");
		free(splited[x]);
		splited[x++] = temp;
	}
	x = 0;
	commands = lstnew(ft_split(splited[x++], ' '));
	while (splited[x])
		lstadd_back(&commands, lstnew(ft_split(splited[x++], ' ')));
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
		data.new_line = 0;
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
