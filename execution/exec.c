#include "../minishell.h"

void	heredoc(t_lst *commands)
{
	int		x;
	int		pipe_fd[2];
	char	*to_add;

	pipe(pipe_fd);
	x = 0;
	to_add = NULL;
	// while (commands)
	// {
	while (commands->content[x])
	{
		if (!ft_strncmp(commands->content[x], "<<", 2))
		{
			while (!to_add || ft_strncmp(to_add, commands->content[x + 1],
				ft_strlen(commands->content[x + 1])))
			{
				to_add = readline("> ");
				write(pipe_fd[WRITE], to_add, ft_strlen(to_add));
				write(pipe_fd[WRITE], "\n", 1);
				free(to_add);
			}
			dup2(pipe_fd[READ], STDIN_FILENO);
		}
		x++;
	}
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]);
	// 	commands = commands->next;
	// }
}

void	handle_command(t_lst *commands)
{
	data.command_code = 1;
	open_files(commands);
	signal(SIGINT, sighandler_cmd);
	signal(SIGQUIT, sighandler_cmd);
	if (data.nb_of_commands == 1)
	{
		heredoc(commands);
		if (handle_one_command(commands) == -1)
			return ; // report error
	}
	else
	{
		if (pipex(commands, STDIN_FILENO) == -1)
			return ; // report error
	}
}

int	handle_one_command(t_lst *commands)
{
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	if (redirect_files(commands) == -1)
		return (-1); // GERER ERREUR
	execute_builtin(commands);
	if (data.command_code != 0)
	{
		commands->pid = fork();
		if (commands->pid < 0)
			return (-1); // GERER ERREUR
		else if (commands->pid == 0)
		{
			if (exec_cmd(commands) == -1)
				return (-1); // GERER ERREUR
		}
		else
		{
			if (redirect_standard(commands) == -1)
				return (-1); // GERER ERREUR
			if (waitpid(-1, &commands->status, 0) == -1)
				return (-1); // GERER ERREUR
		}
	}
	return (0);
		// if (!commands->job_done)
		// {
		// 	write(2, "bash: ", 6);
		// 	write(2, commands->content[0], ft_strlen(commands->content[0]));
		// 	write(2, ": command not found", 19);
		// 	data.command_code = 127;
		// }
}

void	execute_builtin(t_lst *commands)
{
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
	if (data.command_code == 0)
		redirect_standard(commands);
}
