#include "../minishell.h"

void	handle_command(t_lst *commands)
{
	data.command_code = 1;
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	open_files(commands);
	if (data.here_doc != 1)
	{
		signal(SIGINT, sighandler_cmd);
		signal(SIGQUIT, sighandler_cmd);
	}
	if (data.nb_of_commands == 1)
	{
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
	// IF BUILTIN
	// {
		// execute_builtin(commands);
	// 	return (0);
	// }
	// ELSE
	// else
	// {
		commands->pid = fork();
		// signal(SIGQUIT, SIG_IGN);
		if (commands->pid < 0)
			return (-1); // GERER ERREUR
		else if (commands->pid == 0)
		{
			// signal(SIGINT, sighandler_heredoc);
			if (redirect_files(commands) == -1)
				return (-1); // GERER ERREUR
			if (exec_cmd(commands) == -1)
				return (-1); // GERER ERREUR
		}
		else
		{
			if (waitpid(-1, &commands->status, 0) == -1)
				return (-1); // GERER ERREUR
			if (redirect_standard(commands) == -1)
				return (-1); // GERER ERREUR
		}
	// }
	return (0);
}

void	execute_builtin(t_lst *commands)
{
	if (redirect_files(commands) == -1) // LE METTRE AUTRE PART car execute_builtin est appele dans pipex.
		return ; // GERER ERREUR
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
	redirect_standard(commands); // LE METTRE AUTRE PART car execute_builtin est appele dans pipex.
}
