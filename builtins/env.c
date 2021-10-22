/* Reminders:
- Condition to check whether command is 'env' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
*/

#include "../minishell.h"

static void	error_env(char *str)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

int	env(char **splited)
{
	int			i;
	extern char	**environ;

	i = 0;
	if (!ft_strncmp(splited[0], "env", 3))
	{
		if (splited[1])
		{
			error_env(splited[1]);
			return (127);
		}
		while (environ[i] != NULL)
		{
			ft_putendl_fd(environ[i], STDIN_FILENO);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
