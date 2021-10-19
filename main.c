#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
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
	int		num;
	char	*temp;

	num = 0;
	while (commands[num])
		num++;
	temp = ft_strjoin(commands[num - 1], line);
	// to be protected
	free(commands[num - 1]);
	free(line);
	commands[num - 1] = temp;
	return (commands);
}

char	**quote_remover(char **commands)
{
	int		x;
	int		y;
	int		z;
	int		occurences;
	char	*temp;

	x = 0;
	y = 0;
	z = 0;
	while (commands[x])
	{
		occurences = count_occurence(commands[x]);
		temp = malloc(ft_strlen(commands[x]) - occurences + 1);
		// to be protected
		while (commands[x][y])
		{
			if (commands[x][y] != '\'' && commands[x][y] != '\"')
			{
				temp[z] = commands[x][y];
				z++;
			}
			y++;
		}
		temp[z] = '\0';
		free(commands[x]);
		commands[x] = temp;
		z = 0;
		y = 0;
		x++;
	}
	return (commands);
}

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
	char pwd[PATH_MAX];

	if (!ft_strncmp(splited[0], "pwd", 3) && getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
}

void	env(char **splited)
{
	if (!ft_strncmp(splited[0], "env", 3))
	{
		printf("TERM_PROGRAM=%s\n", getenv("TERM_PROGRAM"));
		printf("TERM=%s\n", getenv("TERM"));
		printf("SHELL=%s\n", getenv("SHELL"));
		printf("TMPDIR=%s\n", getenv("TMPDIR"));
		printf("TERM_PROGRAM_VERSION=%s\n", getenv("TERM_PROGRAM_VERSION"));
		printf("TERM_SESSION_ID=%s\n", getenv("TERM_SESSION_ID"));
		printf("ZSH=%s\n", getenv("ZSH"));
		printf("USER=%s\n", getenv("USER"));
		printf("COMMAND_MODE=%s\n", getenv("COMMAND_MODE"));
		printf("SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
		printf("__CF_USER_TEXT_ENCODING=%s\n", getenv("__CF_USER_TEXT_ENCODING"));
		printf("PAGER=%s\n", getenv("PAGER"));
		printf("LSCOLORS=%s\n", getenv("LSCOLORS"));
		printf("PATH=%s\n", getenv("PATH"));
		printf("PWD=%s\n", getenv("PWD"));
		printf("LANG=%s\n", getenv("LANG"));
		printf("ITERM_PROFILE=%s\n", getenv("ITERM_PROFILE"));
		printf("XPC_FLAGS=%s\n", getenv("XPC_FLAGS"));
		printf("XPC_SERVICE_NAME=%s\n", getenv("XPC_SERVICE_NAME"));
		printf("SHLVL=%s\n", getenv("SHLVL"));
		printf("HOME=%s\n", getenv("HOME"));
		printf("COLORFGBG=%s\n", getenv("COLORFGBG"));
		printf("LC_TERMINAL_VERSION=%s\n", getenv("LC_TERMINAL_VERSION"));
		printf("ITERM_SESSION_ID=%s\n", getenv("ITERM_SESSION_ID"));
		printf("LESS=%s\n", getenv("LESS"));
		printf("LOGNAME=%s\n", getenv("LOGNAME"));
		printf("LC_TERMINAL=%s\n", getenv("LC_TERMINAL"));
		printf("SECURITYSESSIONID=%s\n", getenv("SECURITYSESSIONID"));
		printf("COLORTERM=%s\n", getenv("COLORTERM"));
	}
}

void	export(char **splited)
{
	if (!ft_strncmp(splited[0], "export", 6))
	{
		printf("export Apple_PubSub_Socket_Render=%s\n", getenv("Apple_PubSub_Socket_Render"));
		printf("export COLORFGBG=%s\n", getenv("COLORFGBG"));
		printf("export COLORTERM=%s\n", getenv("COLORTERM"));
		printf("export COMMAND_MODE=%s\n", getenv("COMMAND_MODE"));
		printf("export HOME=%s\n", getenv("HOME"));
		printf("export ITERM_PROFILE=%s\n", getenv("ITERM_PROFILE"));
		printf("export ITERM_SESSION_ID=%s\n", getenv("ITERM_SESSION_ID"));
		printf("export LANG=%s\n", getenv("LANG"));
		printf("export LC_TERMINAL=%s\n", getenv("LC_TERMINAL"));
		printf("export LC_TERMINAL_VERSION=%s\n", getenv("LC_TERMINAL_VERSION"));
		printf("export LESS=%s\n", getenv("LESS"));
		printf("export LOGNAME=%s\n", getenv("LOGNAME"));
		printf("export LSCOLORS=%s\n", getenv("LSCOLORS"));
		// OLPWD
		printf("export PAGER=%s\n", getenv("PAGER"));
		printf("export PATH=%s\n", getenv("PATH"));
		printf("export PWD=%s\n", getenv("PWD"));
		printf("export SECURITYSESSIONID=%s\n", getenv("SECURITYSESSIONID"));
		printf("export SHELL=%s\n", getenv("SHELL"));
		printf("export SHLVL=%s\n", getenv("SHLVL"));
		printf("export SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
		printf("export TERM=%s\n", getenv("TERM"));
		printf("export TERM_PROGRAM=%s\n", getenv("TERM_PROGRAM"));
		printf("export TERM_PROGRAM_VERSION=%s\n", getenv("TERM_PROGRAM_VERSION"));
		printf("export TERM_SESSOION_ID=%s\n", getenv("TERM_SESSOION_ID"));
		printf("export TMPDIR=%s\n", getenv("TMPDIR"));
		printf("export USER=%s\n", getenv("USER"));
		printf("export XPC_FLAGS=%s\n", getenv("XPC_FLAGS"));
		printf("export XPC_SERVICE_NAME=%s\n", getenv("XPC_SERVICE_NAME"));
		printf("export ZSH=%s\n", getenv("ZSH"));
		printf("export _=%s\n", getenv("_"));
		printf("export __CF_USER_TEXT_ENCODING=%s\n", getenv("__CF_USER_TEXT_ENCODING"));
	}
}

void	handle_command(char *command, int *exit)
{
	char	**splited;
	int		word_count;
	int		x;

	splited = ft_split(command, ' ');
	// to be protected
	word_count = 0;
	while (splited[word_count])
		word_count++;
	echo(splited, word_count);
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

	x = 0;
	commands = ft_split(line, '|');
	// to be protected
	if (count_occurence(line) % 2 == 1)
	{
		line = readline(">");
		commands = handle_dquote(line, commands);
	}
	commands = quote_remover(commands);
	// to be protected
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

int	main()
 {
	char	*line;
	int 	exit;

	exit = 0;
	while (!exit)
	{
		line = readline("$");
		parser(line, &exit);
		free(line);
	}
	system("leaks a.out");
	return (0);
}
