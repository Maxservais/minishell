#include "pipex.h"

char	**find_paths(char **envp)
{
	int		i;
	char	*env;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen("PATH=")) != NULL)
		{
			env = envp[i];
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

int	exec_cmd(char **cmd, char **envp)
{
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	paths = find_paths(envp);
	if (!paths)
		return (-1);
	i = 0;
	while (paths[i] && access(paths[i], F_OK) != -1)
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd[0]);
		free(part_path);
		free(paths[i]);
		i++;
		execve(path, cmd, paths);
	}
	return (-1);
}
