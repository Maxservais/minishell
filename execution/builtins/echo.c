#include "../../minishell.h"

// char	*dquote(char *line)
// {
// 	char	*new_line;
// 	char	*temp;
// 	char	*temp_2;

// 	new_line = readline("> ");
// 	temp_2 = ft_strjoin(line, "\n");
// 	temp = ft_strjoin(temp_2, new_line);
// 	free(temp_2);
// 	free(line);
// 	free(new_line);
// 	return (temp);
// }

// int	count_occurence(char *str, char c)
// {
// 	int counter;
// 	int	x;

// 	x = 0;
// 	counter = 0;
// 	while (str[x])
// 	{
// 		if (str[x] == c)
// 			counter++;
// 		x++;
// 	}
// 	return (counter);
// }

// char	*remove_useless_quotes(char *line, char first_quote)
// {
// 	char	*new_line;
// 	int		x;
// 	int		y;

// 	x = 0;
// 	y = 0;
// 	new_line = malloc(ft_strlen(line) - count_occurence(line, first_quote) + 1);
// 	while (line[x])
// 	{
// 		if (line[x] == first_quote)
// 			x++;
// 		else
// 			new_line[y++] = line[x++];
// 	}
// 	new_line[y] = '\0';
// 	free(line);
// 	return (new_line);
// }

// int	bad_char(t_lst *command)
// {
// 	if ()
// }

int	echo_base(t_lst *command, int x)
{
	x = 1;
	while (command->cmd[x])
	{
		if (!ft_strcmp(command->content[x], "$?"))
		{
			ft_putnbr(g_data.exit_code);
			if (command->cmd[x + 1])
				write(1, " ", 1);
			x++;
		}
		else if (command->cmd[x + 1])
		{
			write(1, command->cmd[x], ft_strlen(command->cmd[x]));
			write(1, " ", 1);
			x++;
		}
		else
		{
			write(1, command->cmd[x], ft_strlen(command->cmd[x]));
			x++;
		}
	}
	write(1, "\n", 1);
	return (x);
}

int	echo_n(t_lst *command, int x)
{
	x = 2;
	while (command->cmd[x])
	{
		if (command->cmd[x + 1])
		{
			write(1, command->cmd[x], ft_strlen(command->cmd[x]));
			write(1, " ", 1);
			x++;
		}
		else
		{
			write(1, command->cmd[x], ft_strlen(command->cmd[x]));
			x++;
		}
	}
	return (x);
}

int	echo(t_lst *command)
{
	int	x;

	x = 0;
	if (!ft_strcmp(command->cmd[0], "echo") && !command->cmd[1])
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(command->cmd[0], "echo")
		&& ft_strcmp(command->cmd[1], "-n"))
	{
		x = echo_base(command, x);
		return (EXIT_SUCCESS);
	}
	else if (!ft_strcmp(command->cmd[0], "echo")
		&& !ft_strcmp(command->cmd[1], "-n"))
	{
		x = echo_n(command, x);
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
