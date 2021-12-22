#include "../../minishell.h"

int	pwd(t_lst *commands)
{
	char	current_path[PATH_MAX];

	if (getcwd(current_path, sizeof(current_path)))
	{
		if (commands->cmd[1] && !ft_strncmp(commands->cmd[1], "-", 1))
		{
			if (ft_strncmp(commands->cmd[1], "-L", 2)
				&& ft_strncmp(commands->cmd[1], "-P", 2))
			{
				error_usage("pwd: ", commands->cmd[1], "pwd: usage: pwd [-LP]");
				return (EXIT_FAILURE);
			}
		}
		ft_putendl_fd(current_path, STDOUT_FILENO);
	}
	else
	{
		perror("bash: current directory");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
