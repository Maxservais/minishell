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

int	nbr_of_dollars(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	parser_test(char *line)
{
	int			ret;
	int			count;
	t_token		*tokens;
	char		**splited;
	t_lst		*commands;

	if (is_error(line))
		return ;
	ret = 0;
	count = nbr_of_dollars(line);
	while (ft_strchr(line, '$') && ret != count)
		line = add_env(line, &ret, &count);
	if (*line == '\0')
	{
		rl_on_new_line();
		return ;
	}
	tokens = token_finder(line);
	splited = ft_test(line, tokens);
	commands = put_in_list(splited);
	if (add_files(commands) == -1)
	{
		printf("Malloc failed\n");
		return ;
	}
	if (check_syntax(commands) == -1)
		return ;
	remove_files(commands);
	handle_command(commands);
	clean_all(tokens, splited, &commands);
}

char	*ft_space_line(char *line)
{
	int		i;
	int		j;
	char	*line2;

	i = 0;
	j = 0;
	while (line[i] == ' ' || line[i] == '	')
		i++;
	line2 = malloc(sizeof(char) * ((ft_strlen(line) - i) + 1));
	if (!line2)
		return (NULL);
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

void	prompt_test(char *line)
{
	g_data.exit = -1;
	g_data.exit_code = 0;
	while (g_data.exit == -1)
	{
		g_data.here_doc = 0;
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("Minishell$ ");
		if (!line)
		{
			ft_ctrl_d();
			break ;
		}
		add_history(line);
		if (line[0] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			line = ft_strdup("");
		}
		if(line[0] == ' ' || line[0] == '	')
			line = ft_space_line(line);
		if (ft_strlen(line))
			parser_test(line);
		ft_bzero(line, ft_strlen(line));
		free(line);
	}
}

int	main(void)
{
	char	*line;

	tcgetattr(0, &g_data.main_old); // recupere les parametres du terminal
	g_data.main_new = g_data.main_old; //on copie l'ancien terminal
	g_data.main_new.c_lflag&= ~(ECHOCTL); // enleve les caracteres speciaux genre ^C
	tcsetattr(0, TCSANOW, &g_data.main_new); //on definit les parametres avec les modifications
	if (copy_env() == -1)
		return (EXIT_FAILURE);
	line = NULL;
	prompt_test(line);
	// raises an error;
	// -->>
	// free_envp();
	tcsetattr(0, TCSANOW, &g_data.main_old); //on redonne les anciens parametres
	system("leaks minishell");
	return (g_data.exit_code);
}
