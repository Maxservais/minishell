#include "../../minishell.h"

static int	echo_base(t_lst *command, int x)
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

static int	echo_n(t_lst *command, int x)
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
