#include "../minishell.h"

void	handle_command(t_lst *commands)
{
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	if (open_files(commands) == -1 && g_data.nb_of_commands == 1)
		return ;
	if (g_data.here_doc != 1)
	{
		if (!ft_strcmp(commands->content[0], "top"))
			signal(SIGINT, sighandler_cmd1);
		else
			signal(SIGINT, sighandler_cmd);
		signal(SIGQUIT, sighandler_cmd);
	}
	if (g_data.nb_of_commands == 1)
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

int	execute_one_command(t_lst *commands)
{
	commands->pid = fork();
	if (commands->pid < 0)
		return (-1);
	else if (commands->pid == 0)
	{
		if (redirect_files(commands) == -1)
			exit(1);
		exec_cmd(commands, 0);
	}
	else
	{
		if (waitpid(-1, &commands->status, 0) == -1)
			return (-1);
		if (WIFEXITED(commands->status))
			g_data.exit_code = WEXITSTATUS(commands->status);
		if (redirect_standard(commands) == -1)
			return (-1);
	}
	return (0);
}

int	handle_one_command(t_lst *commands)
{
	if (!commands->cmd[0])
	{
		printf("bash: syntax error near unexpected token\n");
		return (-1);
	}
	test_built(commands);
	if (g_data.built == 1)
	{
		if (redirect_files(commands) == -1)
			return (-1);
		execute_builtin(commands);
		redirect_standard(commands);
	}
	else
	{
		if (execute_one_command(commands) == -1)
			return (-1);
	}
	return (0);
}

void	test_built(t_lst *commands)
{
	g_data.built = 0;
	if (!ft_strcmp(commands->cmd[0], "cd")
		|| !ft_strcmp(commands->cmd[0], "echo")
		|| !ft_strcmp(commands->cmd[0], "env")
		|| !ft_strcmp(commands->cmd[0], "exit")
		|| !ft_strcmp(commands->cmd[0], "export")
		|| !ft_strcmp(commands->cmd[0], "pwd")
		|| !ft_strcmp(commands->cmd[0], "unset"))
	{
		g_data.built = 1;
	}
}

void	execute_builtin(t_lst *commands)
{
	if (!ft_strcmp(commands->cmd[0], "cd"))
		g_data.exit_code = cd(commands);
	else if (!ft_strcmp(commands->cmd[0], "echo"))
		g_data.exit_code = echo(commands);
	else if (!ft_strcmp(commands->cmd[0], "env"))
		g_data.exit_code = env(commands);
	else if (!ft_strcmp(commands->cmd[0], "exit"))
		ft_exit(commands);
	else if (!ft_strcmp(commands->cmd[0], "export"))
		g_data.exit_code = export(commands);
	else if (!ft_strcmp(commands->cmd[0], "pwd"))
		g_data.exit_code = pwd(commands);
	else if (!ft_strcmp(commands->cmd[0], "unset"))
		g_data.exit_code = unset(commands);
}
