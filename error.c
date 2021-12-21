#include "minishell.h"

void	command_not_found(t_lst *commands)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, commands->cmd[0],
		ft_strlen(commands->cmd[0]));
	write(STDERR_FILENO, INVALID_COMMAND, ft_strlen(INVALID_COMMAND));
}

void	invalid_file(t_lst *commands, int i)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, commands->infile[i].name,
		ft_strlen(commands->infile[i].name));
	write(STDERR_FILENO, NO_SUCH_FILE, ft_strlen(NO_SUCH_FILE));
	data.exit_code = 1;
}

void	invalid_path(t_lst *commands)
{
	write(STDERR_FILENO, "bash: ", 6);
	write(STDERR_FILENO, commands->cmd[0], ft_strlen(commands->cmd[0]));
	write(STDERR_FILENO, NO_SUCH_FILE, ft_strlen(NO_SUCH_FILE));
}
