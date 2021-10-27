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

// int	exec_cmd(t_lst *command)
// {
// 	int		i;
// 	char	*part_path;
// 	char	*path;
// 	char	**paths;

// 	paths = find_paths();
// 	if (!paths)
// 		return (-1);
// 	i = 0;
// 	while (paths[i] && access(paths[i], F_OK) != -1) // Est-ce qu'on a droit à ACCESS
// 	{
// 		part_path = ft_strjoin(paths[i], "/");
// 		path = ft_strjoin(part_path, command->content[0]);
// 		free(part_path);
// 		free(paths[i]);
// 		i++;
// 		execve(path, command->content, paths);
// 	}
// 	command->job_done = 1;
// 	return (-1);
// }

int	exec_cmd(t_lst *command)
{
	pid_t	pid;
	int		status;
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	pid = fork();
	signal(SIGINT, sighandler_cmd);
	signal(SIGQUIT, sighandler_cmd);
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		paths = find_paths();
		if (!paths)
			return (-1);
		i = 0;
		while (paths[i] && access(paths[i], F_OK) != -1) // Est-ce qu'on a droit à ACCESS
		{
			part_path = ft_strjoin(paths[i], "/");
			path = ft_strjoin(part_path, command->content[0]);
			free(part_path);
			free(paths[i]);
			i++;
			execve(path, command->content, paths);
		}
		return (-1);
	}
	else
	{
		if (waitpid(-1, &status, 0) == -1)
			return (-1);
	}
	command->job_done = 1;
	return (0);
}
