#include "../minishell.h"

void		execute_builtin(t_lst *commands)
{
	// IL FAUT GERER LES REDIRECTIONS!!!!
	if (!ft_strncmp(commands->content[0], "cd", 2))
		data.command_code = cd(commands);
	else if (!ft_strncmp(commands->content[0], "echo", 4))
		data.command_code = echo(commands);
	else if (!ft_strncmp(commands->content[0], "env", 3))
		data.command_code = env(commands);
	else if (!ft_strncmp(commands->content[0], "exit", 5))
		data.command_code = ft_exit(commands);
	else if (!ft_strncmp(commands->content[0], "export", 6))
		data.command_code = export(commands);
	else if (!ft_strncmp(commands->content[0], "pwd", 3))
		data.command_code = pwd(commands);
	else if (!ft_strncmp(commands->content[0], "unset", 5))
		data.command_code = unset(commands);
	// Return Success if at least one builtin command got executed
}

void	handle_command(t_lst *commands)
{
	data.command_code = 1;
	open_files(commands);
	signal(SIGINT, sighandler_cmd);
	signal(SIGQUIT, sighandler_cmd);
	if (data.nb_of_commands == 1)
	{
		execute_builtin(commands);
		if (data.command_code != 0)
		{
			commands->pid = fork();
			if (commands->pid < 0)
				return ; // RETURN ERROR
			else if (commands->pid == 0)
			{
				// if input files, redirect
				if (commands->infile->name && commands->infile[last_infile(commands)].fd)
				{
					if (dup2(commands->infile[last_infile(commands)].fd, STDIN_FILENO) == -1)
						return ;
					close(commands->infile[last_infile(commands)].fd);
				}
				// if output files, redirect
				if (commands->outfile->name && commands->outfile[last_outfile(commands)].fd)
				{
					if (dup2(commands->outfile[last_outfile(commands)].fd, STDOUT_FILENO) == -1)
						return ;
					close(commands->outfile[last_outfile(commands)].fd);
				}
				// Execute command
				if (exec_cmd(commands) == -1)
					return ;
			}
			else
			{
				if (waitpid(-1, &commands->status, 0) == -1)
					return ;
			}
		}
		// if (!commands->job_done)
		// {
		// 	write(2, "bash: ", 6);
		// 	write(2, commands->content[0], ft_strlen(commands->content[0]));
		// 	write(2, ": command not found", 19);
		// 	data.command_code = 127;
		// }
	}
	else
	{
		if (pipex(commands, STDIN_FILENO) == -1)
			return ; // report error
	}
}

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

	// execute_builtin(command);
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
	exit(127);
	command->job_done = 1;
	return (-1);
}
