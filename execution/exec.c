#include "../minishell.h"

void	handle_command(t_lst *commands)
{
	data.command_code = -1;
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	open_files(commands);
	if (data.here_doc != 1)
	{
		if (!ft_strcmp(commands->content[0], "top"))
			signal(SIGINT, sighandler_cmd1);
		else
			signal(SIGINT, sighandler_cmd);
		signal(SIGQUIT, sighandler_cmd);
	}
	if (data.nb_of_commands == 1)
	{
		if (handle_one_command(commands) == -1)
			return ; // report error
		if (commands->status > 256 && data.built == 0)
		{
			write(2, "bash: ", 6);
			write(2, commands->content[0], ft_strlen(commands->content[0]));
			write(2, ": command not found\n", 20);
			data.exit_code = 127;
		}
	}
	else
	{
		if (pipex(commands, STDIN_FILENO) == -1)
			return ; // report error
	}
}

int	handle_one_command(t_lst *commands)
{
	test_built(commands);
	/* IF BUILTIN */
	if (data.built == 1)
	{
		if (redirect_files(commands) == -1)
			return (-1); // GERER ERREUR
		execute_builtin(commands);
		redirect_standard(commands);
	}
	/* ELSE */
	else
	{
		commands->pid = fork();
		if (commands->pid < 0)
			return (-1); // GERER ERREUR
		else if (commands->pid == 0)
		{
			if (redirect_files(commands) == -1)
				return (-1); // GERER ERREUR
			if (exec_cmd(commands) == -1)
				return (-1); // GERER ERREUR
		}
		else
		{
			if (waitpid(-1, &commands->status, 0) == -1)
				return (-1); // GERER ERREUR
			if (commands->status >= 256)
			{
				if (data.here_doc == 1)
					commands->status = 256;
				data.exit_code = 1;
				return (0); // check return type
			}
			else if (commands->status < 256)
			{
				data.exit_code = 0;
				return (0); // check return type
			}
			if (redirect_standard(commands) == -1)
				return (-1); // GERER ERREUR
		}
	}
	return (0);
}

void	test_built(t_lst *commands)
{
	data.built = 0;
	if (!ft_strcmp(commands->content[0], "cd")
		|| !ft_strcmp(commands->content[0], "echo") 
		|| !ft_strcmp(commands->content[0], "env")
		|| !ft_strcmp(commands->content[0], "exit")
		|| !ft_strcmp(commands->content[0], "export")
		|| !ft_strcmp(commands->content[0], "pwd")
		|| !ft_strcmp(commands->content[0], "unset"))
		{
			data.built = 1;
			data.command_code = 0;
		}
}

void	execute_builtin(t_lst *commands)
{
	// test_built(commands);
	if (!ft_strcmp(commands->content[0], "cd"))
		data.exit_code = cd(commands);
	else if (!ft_strcmp(commands->content[0], "echo"))
		data.exit_code = echo(commands);
	else if (!ft_strcmp(commands->content[0], "env"))
		data.exit_code = env(commands);
	else if (!ft_strcmp(commands->content[0], "exit"))
		ft_exit(commands);
	else if (!ft_strcmp(commands->content[0], "export"))
		data.exit_code = export(commands);
	else if (!ft_strcmp(commands->content[0], "pwd"))
		data.exit_code = pwd(commands);
	else if (!ft_strcmp(commands->content[0], "unset"))
		data.exit_code = unset(commands);
	// Return Success if at least one builtin command got executed
}
