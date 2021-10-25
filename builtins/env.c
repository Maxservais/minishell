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

int	env(t_lst *commands)
{
	int			i;
	extern char	**environ;

	i = 0;
	if (commands->content[1])
	{
		error_env(commands->content[1]);
		return (127);
	}
	while (environ[i] != NULL)
	{
		ft_putendl_fd(environ[i], STDIN_FILENO);
		i++;
	}
	commands->job_done = 1;
	return (EXIT_SUCCESS);
}

/* si env -eje, erreur below:
		env: illegal option -- e
		usage: env [-iv] [-P utilpath] [-S string] [-u name]
           [name=value ...] [utility [argument ...]] */