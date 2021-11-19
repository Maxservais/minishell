#include "minishell.h"

void	is_error(t_lst *command)
{
	int simple_quote;
	int double_quote;
	int x;

	simple_quote = 0;
	double_quote = 0;
	x = 0;
	while (command->content[x])
	{
		if (*command->content[x] == '\'')
			simple_quote++;
		if (*command->content[x] == '\"')
			double_quote++;
		x++;
	}
	if (simple_quote % 2 == 1 || double_quote % 2 == 1)
		ft_putstr_fd("error\n", 1);
}

void	parser_test(char *line)
{
	t_token		*tokens;
	char		**splited;
	t_lst		*commands;

	tokens = token_finder(line);
	splited = ft_test(line, tokens);
	commands = put_in_list(splited);
	add_files(&commands);
	remove_files(&commands);
	handle_command(commands);
	clean_all(tokens, splited, &commands);
}

void	prompt_test(char *line)
{
	data.exit = -1;
	while (data.exit == -1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("ta_mère$ ");
		if (!line)
		{
			ft_ctrl_d();
			break ;
		}
		add_history(line);
		if (ft_strlen(line))
			parser_test(line);
		free(line);
	}
}

int	main(void)
 {
	char	*line;

	// FIX SEGV ERROR
	copy_env(); // check if succesful execution or not
	line = NULL;
	prompt_test(line);

	// raises an error;
	// -->>
	// free_envp();
	system("leaks minishell");
	return (EXIT_SUCCESS);
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
