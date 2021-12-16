/* Reminders:
- retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
- unset does two things: 
1) remove an environment variable from the list of exported variables
2) remove a shell variable
*/

#include "../../minishell.h"

static void	find_var(char *variable)
{
	int			i;

	i = 0;
	// strcmp plutot?
	while (ft_strncmp(data.envp[i], variable, ft_strlen(variable)))
			i++;
	free(data.envp[i]);
	// ft_bzero(data.envp[i], ft_strlen(data.envp[i]));
}

int	unset(t_lst *commands)
{
	if (!ft_strncmp(commands->content[1], "-", 1))
	{
		if (ft_strcmp(commands->content[1], "-f")
			&& ft_strcmp(commands->content[1], "-v"))
		{
			error_usage("unset: ", commands->content[1],
				"unset: usage: unset [-f] [-v] [name ...]");
			// commands->job_done = 1;
			return (EXIT_FAILURE);
		}
	}
	else if (commands->content[1])
		find_var(commands->content[1]);
	// commands->job_done = 1;
	return (EXIT_SUCCESS);
}
