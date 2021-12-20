/* Reminders:
- Condition to check whether command is 'env' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../../minishell.h"

int	ft_exit(t_lst *commands)
{
	write(STDOUT_FILENO, "exit\n", 5);
	if ((commands->args == 2 || commands->args >= 3)
		&& strisdigit(commands->cmd[1]) == -1)
	{
		write(STDERR_FILENO, "bash: ", 6);
		write(STDERR_FILENO, commands->cmd[1], ft_strlen(commands->cmd[1]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		data.exit_code = 255;
		data.exit = 1;
	}
	else if (commands->args >= 3 && strisdigit(commands->cmd[1]) == 0)
	{
		write(STDERR_FILENO, "bash: exit: too many arguments\n", 31);
		data.exit_code = 1;
	}
	else if (commands->args == 2 && strisdigit(commands->cmd[1]) == 0)
	{
		data.exit_code = ft_atoi(commands->cmd[1]);
		data.exit = 1;
	}
	else
		data.exit = 1;
	return (0);
}
