#include "../../minishell.h"

int	ft_exit(t_lst *commands)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if ((commands->args == 2 || commands->args >= 3)
		&& ft_strisdigit(commands->cmd[1]) == -1)
	{
		write(STDERR_FILENO, "bash: ", 6);
		write(STDERR_FILENO, commands->cmd[1], ft_strlen(commands->cmd[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		g_data.exit_code = 255;
		g_data.exit = 1;
	}
	else if (commands->args >= 3 && ft_strisdigit(commands->cmd[1]) == 0)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
		g_data.exit_code = 1;
	}
	else if (commands->args == 2 && ft_strisdigit(commands->cmd[1]) == 0)
	{
		g_data.exit_code = ft_atoi(commands->cmd[1]);
		g_data.exit = 1;
	}
	else
		g_data.exit = 1;
	return (0);
}
