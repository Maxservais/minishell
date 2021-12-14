#include "../minishell.h"

void	handle_command(t_lst *commands)
{
	data.command_code = -1;
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	if (open_files(commands) == -1 && data.nb_of_commands == 1)
		return ;
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
			return ;
	}
	else
	{
		if (pipex(commands, STDIN_FILENO) == -1)
			return ;
	}
	close_files(commands);
}

int	handle_one_command(t_lst *commands)
{
	/* IF BUILTIN */
	test_built(commands);
	if (data.built == 1)
	{
		if (redirect_files(commands) == -1)
			return (-1);
		execute_builtin(commands);
		redirect_standard(commands);
	}
	/* ELSE */
	else
	{
		commands->pid = fork();
		if (commands->pid < 0)
			return (-1);
		else if (commands->pid == 0)
		{
			if (redirect_files(commands) == -1)
				exit(1);
			exec_cmd(commands);
		}
		else
		{
			if (waitpid(-1, &commands->status, 0) == -1)
				return (-1);
			if (WIFEXITED(commands->status))
				data.exit_code = WEXITSTATUS(commands->status);
			if (redirect_standard(commands) == -1)
				return (-1);
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
