/* Reminders:
- Is return value the right one - 0 or 1?
*/

#include "../minishell.h"

int	pwd(t_lst *commands)
{
	char	current_path[PATH_MAX];

	if (getcwd(current_path, sizeof(current_path)))
	{
		if (commands->content[1] && !ft_strncmp(commands->content[1], "-", 1))
		{
			if (ft_strncmp(commands->content[1], "-L", 2)
				&& ft_strncmp(commands->content[1], "-P", 2))
			{
				error_usage("pwd: ", commands->content[1], "pwd: usage: pwd [-LP]");
				commands->job_done = 1;
				return (EXIT_FAILURE);
			}
		}
		ft_putendl_fd(current_path, 1);
	}
	else
	{
		perror("bash: pwd");
		commands->job_done = 1;
		return (EXIT_FAILURE);
	}
	commands->job_done = 1;
	return (EXIT_SUCCESS);
}
