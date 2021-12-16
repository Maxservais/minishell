#include "minishell.h"

int	is_error(char *line)
{
	int simple_quote;
	int double_quote;

	simple_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			simple_quote++;
		if (*line == '\"')
			double_quote++;
		line++;
	}
	if (simple_quote % 2 == 1 || double_quote % 2 == 1)
	{
		ft_putstr_fd("input error\n", 1);
		return (1);
	}
	return (0);
}

void	parser_test(char *line)
{
	t_token		*tokens;
	char		**splited;
	t_lst		*commands;

	if (is_error(line))
		return ;
	tokens = token_finder(line);
	splited = ft_test(line, tokens);
	commands = put_in_list(splited);
	add_files(commands);
	remove_files(&commands);
	handle_command(commands);
	// DO WE REALLY FREE EVERYTHING HERE? NO MEMORY LEAKS?
	clean_all(tokens, splited, &commands);
}

char	*ft_space_line(char *line)
{
	int		i;
	int		j;
	char	*line2;

	i = 0;
	j = 0;
	line2 = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	line2 = malloc(sizeof(char) * ((ft_strlen(line) - i) + 1));
	while (line[i])
	{
		line2[j] = line[i];
		j++;
		i++;
	}
	free(line);
	line2[j] = '\0';
	return (line2);
}

/*la ligne 85/86 supprime les espace et les tabulations*/

void	prompt_test(char *line)
{
	data.exit = -1;
	data.exit_code = 0;
	while (data.exit == -1)
	{
		data.here_doc = 0;
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("Minishell$ ");
		if (!line)
		{
			ft_ctrl_d();
			break ;
		}
		add_history(line);
		if(line[0] == ' ' || line[0] == '	')
			line = ft_space_line(line);
		if (ft_strlen(line))
			parser_test(line);
		free(line);
	}
}

int	main(void)
{
	char	*line;

	// FIX SEGV ERROR WHEN SPACE OR TAB IS INPUT
	tcgetattr(0, &data.main_old);// recupere les parametres du terminal
	data.main_new = data.main_old;//on copie l'ancien terminal
	data.main_new.c_lflag&= ~(ECHOCTL);// enleve les caracteres speciaux genre ^C
	tcsetattr(0, TCSANOW, &data.main_new);//on definit les parametres avec les modifications
	if (copy_env() == -1)
		return (EXIT_FAILURE);
	// check if succesful execution or not
	// data.here_doc = 0;
	line = NULL;
	prompt_test(line);
	// raises an error;
	// -->>
	// free_envp();
	tcsetattr(0, TCSANOW, &data.main_old);//on redonne les anciens parametres
	//system("leaks minishell");
	return (data.exit_code);
}

// void	parser_lst(char *line)
// {
// 	t_lst	*commands;
// 	char	**splited;
// 	char	*temp;
// 	int		x;

// 	data.nb_of_commands = 0;
// 	splited = ft_split(line, '|');
// 	x = 0;
// 	while (splited[x])
// 	{
// 		data.nb_of_commands++;
// 		temp = ft_strtrim(splited[x], " ");
// 		free(splited[x]);
// 		splited[x++] = temp;
// 	}
// 	x = 0;
// 	commands = lstnew(ft_split(splited[x], ' '), x + 1);
// 	x++;
// 	while (splited[x])
// 	{
// 		lstadd_back(&commands, lstnew(ft_split(splited[x], ' '), x + 1));
// 		x++;
// 	}
// 	x = 0;
// 	while (splited[x])
// 		free(splited[x++]);
// 	free(splited);
// 	// sub_parser(line);
// 	// check if there is input file
// 	// handle_command(commands);
// 	lstclear(&commands);
// }

// void	prompt(char *line)
// {
// 	char	first_quote;

// 	data.exit = -1;
// 	while (data.exit == -1)
// 	{
// 		data.nb_of_commands = 0;
// 		signal(SIGINT, sighandler);
// 		// signal(SIGQUIT, SIG_IGN);
// 		line = readline("tamere-3.2$ ");
// 		if (!line)
// 		{
// 			ft_ctrl_d();
// 			break;
// 		}
// 		if (ft_strlen(line))
// 		{
// 			first_quote = find_first_quote(line);
// 			while (count_occurence(line, first_quote) % 2 == 1)
// 				line = dquote(line);
// 			line = remove_useless_quotes(line, first_quote);
// 			line = add_env(line);
// 			parser_lst(line);
// 		}
// 		free(line);
// 	}
// 	if (data.exit == 1)
// 	{
// 		// system("leaks minishell");
// 		exit (EXIT_SUCCESS);
// 	}
// }
