/* Reminders:
- Improve Return codes
*/

#include "../minishell.h"

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
	ft_putendl_fd("usage: env [-iv] [-P utilpath] [-S string] [-u name]", STDERR_FILENO);
	ft_putendl_fd("\t [name=value ...] [utility [argument ...]]", STDERR_FILENO);
	free((void *)option);
}

int	env(t_lst *commands)
{
	int			i;
	extern char	**environ;

	i = 0;
	if (commands->content[1] && !ft_strncmp(commands->content[1], "-", 1))
	{
		if (ft_strncmp(commands->content[1], "-i", 2)
			&& ft_strncmp(commands->content[1], "-V", 2))
		{
			error_usage_env(commands->content[1]);
			commands->job_done = 1;
			return (EXIT_FAILURE);
		}
	}
	else if (commands->content[1])
	{
		error_env(commands->content[1]);
		commands->job_done = 1;
		return (127);
	}
	while (data.envp[i] != NULL)
	{
		ft_putendl_fd(data.envp[i], STDIN_FILENO);
		i++;
	}
	commands->job_done = 1;
	return (EXIT_SUCCESS);
}
