/* Reminders:
- Improve Return codes
*/

#include "../../minishell.h"

static void	error_env(char *str)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

static void	error_usage_env(char *str)
{
	char	*option;

	option = ft_substr(str, 0, 2);
	ft_putstr_fd("env: illegal option -", STDERR_FILENO);
	ft_putendl_fd(option, STDERR_FILENO);
	ft_putendl_fd("usage: env [-iv] [-P utilpath] [-S string] [-u name]",
		STDERR_FILENO);
	ft_putendl_fd("\t [name=value ...] [utility [argument ...]]", STDERR_FILENO);
	free((void *)option);
}

int	copy_env(void)
{
	int			i;
	int			counter;
	extern char	**environ;

	i = 0;
	counter = 0;
	while (environ[counter] != NULL)
		counter++;
	data.envp = malloc(sizeof(char *) * (counter + 1));
	if (!data.envp)
		return (-1);
	while (environ[i] != NULL)
	{
		data.envp[i] = strdup(environ[i]);
		// check for errors and free
		i++;
	}
	data.envp[i] = NULL;
	return (EXIT_SUCCESS);
}

int	env(t_lst *commands)
{
	int			i;

	i = 0;
	if (commands->cmd[1] && !ft_strncmp(commands->cmd[1], "-", 1))
	{
		if (ft_strncmp(commands->cmd[1], "-i", 2)
			&& ft_strncmp(commands->cmd[1], "-V", 2))
		{
			error_usage_env(commands->cmd[1]);
			return (EXIT_FAILURE);
		}
	}
	else if (commands->cmd[1]) //A QUOI CA SERT?
	{
		error_env(commands->cmd[1]);
		return (127);
	}
	while (data.envp[i] != NULL)
	{
		ft_putendl_fd(data.envp[i], STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}
