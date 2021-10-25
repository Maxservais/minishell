/* Reminders:
- Condition to check whether command is 'pwd' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../minishell.h"

static void	error_pwd(char *str)
{
	char	*err;

	err = ft_substr(str, 0, 2);
	ft_putstr_fd("bash: pwd: ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("pwd: usage: pwd [-LP]", STDERR_FILENO);
	free((void *)err);
}

int	pwd(char **splited)
{
	char	current_path[PATH_MAX];

	if (!ft_strncmp(splited[0], "pwd", 3))
	{
		if (getcwd(current_path, sizeof(current_path)))
		{
			if (splited[1] && !ft_strncmp(splited[1], "-", 1))
			{
				if (ft_strncmp(splited[1], "-L", 2)
					&& ft_strncmp(splited[1], "-P", 2))
				{
					error_pwd(splited[1]);
					return (EXIT_FAILURE);
				}
			}
			ft_putendl_fd(current_path, 1);
		}
		else
		{
			perror("bash: error");
			return (EXIT_FAILURE);
		}
	//		command->job_done = 1;
	}
	return (EXIT_SUCCESS);
}
