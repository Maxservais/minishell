#include "../minishell.h"

void	ft_exit(t_lst command)
{
	if (!ft_strncmp(command.content[0], "exit", 5))
		data.exit = 1;
}
