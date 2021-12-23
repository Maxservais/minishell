#include "../minishell.h"

static void	ft_exec(t_lst *command, int err)
{
	if (err != -1)
	{
		test_built(command);
		if (g_data.built == 1)
		{
			execute_builtin(command);
			exit(g_data.exit_code);
		}
		else
			exec_cmd(command, 0);
	}
	else
		exit(1);
}

int	first_command(int right_pipe[], t_lst *command)
{
	int	err;

	if (!command->cmd[0])
		return (-1);
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		err = redirect_files(command);
		close(right_pipe[READ]);
		if (!command->outfile->name)
			if (dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		close(right_pipe[WRITE]);
		ft_exec(command, err);
	}
	else
	{
		close(right_pipe[WRITE]);
		if (pipex(command->next, right_pipe) == -1)
			return (-1);
	}
	return (0);
}

int	last_command(int left_pipe[], int right_pipe[], t_lst *command)
{
	int	err;

	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		err = redirect_files(command);
		if (!command->infile->name)
		{
			if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		}
		close(left_pipe[READ]);
		ft_exec(command, err);
	}
	else
	{
		close(right_pipe[READ]);
		close(right_pipe[WRITE]);
		close(left_pipe[READ]);
	}
	return (0);
}

int	inter_command(int l_pipe[], int r_pipe[], t_lst *command, int err)
{
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		err = redirect_files(command);
		close(r_pipe[READ]);
		if (!command->outfile->name)
			if (dup2(r_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		close(r_pipe[WRITE]);
		if (!command->infile->name)
			if (dup2(l_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		close(l_pipe[READ]);
		ft_exec(command, err);
	}
	else
	{
		close(l_pipe[READ]);
		close(r_pipe[WRITE]);
		if (pipex(command->next, r_pipe) == -1)
			return (-1);
	}
	return (0);
}

int	pipex(t_lst *command, int left_pipe[])
{
	int		right_pipe[2];

	if (pipe(right_pipe) == -1)
		return (pipe_error());
	if (command->index == 1)
	{
		if (first_command(right_pipe, command) == -1)
			return (-1);
	}
	else if (command->index == g_data.nb_of_commands)
	{
		if (last_command(left_pipe, right_pipe, command) == -1)
			return (-1);
	}
	else
	{
		if (inter_command(left_pipe, right_pipe, command, 0) == -1)
			return (-1);
	}
	waitpid(-1, &command->status, 0);
	if (WIFEXITED(command->status))
		g_data.exit_code = WEXITSTATUS(command->status);
	return (0);
}
