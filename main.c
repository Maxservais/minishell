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
	else if (!ft_strncmp(commands->content[0], "unset", 5))
		unset(commands);
	// Return Success if at least one builtin command got executed
	return (0);
}

int		copy_env(void)
{
	int			i;
	int			counter;
	extern char	**environ;

	i = 0;
	counter = 0;
	while (environ[counter] != NULL)
		counter++;
	data.envp = malloc(sizeof(char *) * counter + 1);
	while (environ[i] != NULL)
	{
		data.envp[i] = strdup(environ[i]);
		// check for errors and free
		i++;
	}
	data.envp[i] = NULL;
	return (EXIT_SUCCESS);
}

void	handle_command(t_lst *commands)
{
	while (commands)
	{
		// open_files(commands);
		// IF INPUT FILE(S)
		// REDIRECT FROM LATEST INPUT FILE
		execute_builtin(commands);
		exec_cmd(commands);
		// pipex(commands, STDIN_FILENO); // report error if -1
		// execute pipe
		// execute redirection to last OUTPUT FILE
		// IF NO REDIRECTION, SEND OUTPUT TO STDOUT_FILENO
		if (!commands->job_done)
		{
			printf("bash: %s: command not found\n", commands->content[0]);
			data.command_code = 127;
		}
		commands = commands->next;
	}
}

void	sub_parser(t_lst *commands)
{
	int	x;
	int	y;
	int	z;

	while (commands)
	{
		x = 0;
		y = 0;
		z = 0;
		commands->infile = malloc(sizeof(t_file) * count_occurence(commands->content[x], '<') + 1);
		commands->outfile = malloc(sizeof(t_file) * count_occurence(commands->content[x], '>') + 1);
		while (commands->content[x])
		{
			if (count_occurence(commands->content[x], '<') > 0)
			{
				commands->infile[y].name = commands->content[x + 1];
				commands->infile[y].mode = 1;
				y++;
			}
			if (count_occurence(commands->content[x], '>') > 0)
			{
				commands->outfile[z].name = commands->content[x + 1];
				commands->outfile[z].mode = 2;
				z++;
			}
			x++;
		}
		commands->infile[y].name = NULL;
		commands->outfile[z].name = NULL;
		commands = commands->next;
	}
}

void	parser_lst(char *line)
{
	t_lst	*commands;
	char	**splited;
	char	*temp;
	int		x;

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
	x = 0;
	while (splited[x])
		free(splited[x++]);
	free(splited);
	sub_parser(commands);
	// check if there is input file
	handle_command(commands);
	lstclear(&commands);
}

int	char_position(char *line, char c)
{
	int	position;

	position = 0;
	while (line[position])
	{
		if (line[position] == c)
			return (position);
		position++;
	}
	return (-1);

}

int	space_position(char *line, char c, int start)
{
	int	position;

	position = start;
	while (line[position])
	{
		if (line[position] == c)
			return (position);
		position++;
		if (!line[position])
			return (position);
	}
	return (-1);
}

char	*add_env(char *line)
{
	int			x;
	int			dollar;
	int			space;
	char		*key;
	char		*string_before;
	char		*string_after;
	char		*value;
	char		*temp;
	char		*new_line;

	x = 0;
	value = NULL;
	dollar = char_position(line, '$');
	space = space_position(line, ' ', dollar);
	if (dollar >= 0)
	{
		key = ft_substr(line, dollar + 1, space - dollar);
		string_before = ft_substr(line, 0, dollar);
		string_after = ft_substr(line, space, ft_strlen(line));
		while (data.envp[x])
		{
			if (!ft_strncmp(data.envp[x], key, ft_strlen(key) - 1))
			{
				value = ft_substr(data.envp[x], ft_strlen(key) + 1, ft_strlen(data.envp[x]) - 1);
				break ;
			}
			x++;
		}
		temp = ft_strjoin(string_before, value);
		free(value);
		free(string_before);
		new_line = ft_strjoin(temp, string_after);
		free(string_after);
		free(temp);
		free(key);
		free(line);
		return (new_line);
	}
	return (line);
}

char	*prompt1(char *line)
{
	char	first_quote;

	first_quote = find_first_quote(line);
	while (count_occurence(line, first_quote) % 2 == 1)
		line = dquote(line);
	line = remove_useless_quotes(line, first_quote);
	line = add_env(line);
	parser_lst(line);
	return (line);
}

void	prompt(char *line)
{
	copy_env(); // check if succesful execution or not
	data.exit = -1;
	while (data.exit == -1)
	{
		data.nb_of_commands = 0;
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("Minishell> ");
		if (!line)
		{
			ft_ctrl_d();
			break;
		}
		else if (ft_strlen(line))
			line = prompt1(line);
		free(line);
	}
	if (data.exit == 1)
	{
		system("leaks minishell");
		exit (EXIT_SUCCESS);
	}
}

void	free_envp(void)
{
	int	x;

	x = 0;
	while (data.envp[x])
	{
		free(data.envp[x]);
		x++;
	}
	free(data.envp);
}

int	main(void)
 {
	char	*line;

	line = NULL;
	prompt(line);
	system("leaks minishell");
	free_envp();
	return (EXIT_SUCCESS);
}
