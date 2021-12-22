#include "../../minishell.h"

static void	add_to_env(char *variable)
{
	int		i;
	char	current_path[PATH_MAX];

	i = 0;
	getcwd(current_path, sizeof(current_path));
	while (g_data.envp[i] != NULL)
	{
		if (!ft_strncmp(g_data.envp[i], "PWD=", ft_strlen("PWD=")))
		{
			free(g_data.envp[i]);
			g_data.envp[i] = ft_strjoin("PWD=", current_path);
		}
		if (ft_strnstr(g_data.envp[i], "OLDPWD=", ft_strlen("OLDPWD=")) != NULL)
		{
			free(g_data.envp[i]);
			g_data.envp[i] = variable;
		}
		i++;
	}
}

static int	cd_flag(t_lst *commands)
{
	if (ft_strcmp(commands->cmd[1], "-L")
		&& ft_strcmp(commands->cmd[1], "-P"))
	{
		error_usage("cd: ", commands->cmd[1],
			"cd: usage: cd [-L|-P] [dir]");
		return (EXIT_FAILURE);
	}
	else
		chdir(commands->cmd[2]);
	return (EXIT_SUCCESS);
}

static int	find_home(void)
{
	int	i;

	i = 0;
	while (g_data.envp[i])
	{
		if (!ft_strncmp(g_data.envp[i], "HOME", ft_strlen("HOME")))
			return (0);
		i++;
	}
	return (-1);
}

int	cd(t_lst *commands)
{
	char	current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));
	if (!commands->cmd[1])
	{
		if (find_home() != -1)
			chdir(getenv("HOME"));
		else
			printf("bash: cd: HOME not set\n");
	}
	else if (!ft_strcmp(commands->cmd[1], "\0"))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(commands->cmd[1], "-", 1))
	{
		if (cd_flag(commands) == 1)
			return (EXIT_FAILURE);
	}
	else if (chdir(commands->cmd[1]) == -1)
	{
		error_cmd("bash: ", "cd: ", commands->cmd[1]);
		return (EXIT_FAILURE);
	}
	add_to_env(ft_strjoin("OLDPWD=", current_path));
	return (EXIT_SUCCESS);
}
