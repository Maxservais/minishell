#include "../../minishell.h"

int	find_var(char *variable)
{
	int	i;

	i = 0;
	while (g_data.envp[i] && ft_strncmp(g_data.envp[i],
			variable, ft_strlen(variable)))
		i++;
	if (g_data.envp[i] && !ft_strcmp_unset(g_data.envp[i], variable))
	{
		free(g_data.envp[i]);
		ft_bzero(g_data.envp[i], ft_strlen(g_data.envp[i]));
		while (g_data.envp[i])
		{
			g_data.envp[i] = g_data.envp[i + 1];
			i++;
		}
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	unset(t_lst *commands)
{
	if (!ft_strncmp(commands->cmd[1], "-", 1))
	{
		if (ft_strcmp(commands->cmd[1], "-f")
			&& ft_strcmp(commands->cmd[1], "-v"))
		{
			error_usage("unset: ", commands->cmd[1],
				"unset: usage: unset [-f] [-v] [name ...]");
			return (EXIT_FAILURE);
		}
		else if (find_var(commands->cmd[2]) == 1)
			return (EXIT_FAILURE);
	}
	else if (commands->cmd[1])
		if (find_var(commands->cmd[1]) == 1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
