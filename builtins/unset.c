/* Reminders:
- retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
- unset does two things: 
1) remove an environment variable from the list of exported variables
2) remove a shell variable
*/

#include "../minishell.h"

static void	find_var(char *variable)
{
	int			i;

	i = 0;
	while (strncmp(data.envp[i], variable, ft_strlen(variable)))
			i++;
	free(data.envp[i]);
	// ft_bzero(data.envp[i], ft_strlen(data.envp[i]));
}

int	unset(t_lst *commands)
{
	if (commands->content[1])
		find_var(commands->content[1]);
	// else if (!ft_strncmp(commands->content[1], "-", 1))
	// {
	// 	if (ft_strncmp(commands->content[1], "-L", 2)
	// 		&& ft_strncmp(commands->content[1], "-P", 2))
	// 	{
	// 		error_usage("cd: ", commands->content[1], "cd: usage: cd [-L|-P] [dir]");
	// 		commands->job_done = 1;
	// 		return (EXIT_FAILURE);
	// 	}
	// }
	commands->job_done = 1;
	return (1); // a changer
}
