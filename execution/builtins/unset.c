/* Reminders:
- retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
- unset does two things: 
1) remove an environment variable from the list of exported variables
2) remove a shell variable
*/

#include "../../minishell.h"

int	find_var(char *variable)
{
	int			i;

	i = 0;
	while (data.envp[i] && ft_strncmp(data.envp[i],
			variable, ft_strlen(variable)))
		i++;
	if (data.envp[i] && !ft_strcmp_unset(data.envp[i], variable))
	{
		free(data.envp[i]);
		ft_bzero(data.envp[i], ft_strlen(data.envp[i]));
		while (data.envp[i])
		{
			data.envp[i] = data.envp[i + 1];
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
