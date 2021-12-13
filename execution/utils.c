#include "../minishell.h"

char	**find_paths(void)
{
	int		i;
	char	*env;
	char	**paths;

	i = 0;
	while (data.envp[i] != NULL)
	{
		if (ft_strnstr(data.envp[i], "PATH=", ft_strlen("PATH=")) != NULL)
		{
			env = data.envp[i];
			break ;
		}
		i++;
	}
	paths = ft_split(ft_substr(env, ft_strlen("PATH="),
				ft_strlen(env)), ':');
	if (!paths)
		return (NULL);
	return (paths);
}

void	exec_cmd(t_lst *command)
{
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	paths = find_paths();
	if (!paths)
	{
		invalid_path(command);
		exit(127);
	}
	i = 0;
	if (execve(command->cmd[0], command->cmd, data.envp) == -1)
	{
		while (paths[i])
		{
			part_path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(part_path, command->cmd[0]);
			free(part_path);
			free(paths[i]);
			i++;
			execve(path, command->cmd, data.envp);
		}
	}
	command_not_found(command);
	// printf("code2 %d\n", data.exit_code);
	exit (127);
}
