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

int	exec_cmd(t_lst *command)
{
	int		i;
	char	*part_path;
	char	*path;
	char	**paths;

	execute_builtin(command);
	if (data.command_code == 0)
		return (0);
	paths = find_paths();
	if (!paths)
		return (-1);
	i = 0;
	execve(command->cmd[0], command->cmd, data.envp);
	// int x;
	// while (command)
	// {
	// 	x = 0;
	// 	while (command->cmd[x])
	// 		printf("cmd: %s\n", command->cmd[x++]);
	// 	command = command->next;
	// }
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, command->cmd[0]);
		free(part_path);
		free(paths[i]);
		i++;
		execve(path, command->cmd, data.envp);
	}
	command->job_done = 1;
	return (-1);
}
