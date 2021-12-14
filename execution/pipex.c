#include "../minishell.h"

int	first_command(int right_pipe[], t_lst *command)
{
	int	err;

	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		err = redirect_files(command);
		/* Close unused side of the right pipe */
		close(right_pipe[READ]);
		/* Only write to pipe if there was no output file */
		if (!command->outfile->name)
			if (dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		close(right_pipe[WRITE]);
		/* Execute command */
		if (err != -1)
		{
			test_built(command);
			if (data.built == 1)
			{
				execute_builtin(command);
				exit(data.exit_code);
			}
			else
				exec_cmd(command);
		}
		else
			exit(1);
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
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		err = redirect_files(command);
		/* Only read from left pipe if there was no input file */
		if (!command->infile->name)
		{
			if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		}
		close(left_pipe[READ]);
		/* Execute command */
		if (err != -1)
		{
			test_built(command);
			if (data.built == 1)
			{
				execute_builtin(command);
				exit(data.exit_code);
			}
			else
				exec_cmd(command);
		}
		else
			exit(1);
	}
	else
	{
		close(right_pipe[READ]);
		close(right_pipe[WRITE]);
		close(left_pipe[READ]);
	}
	return (0);
}

int	inter_command(int l_pipe[], int r_pipe[], t_lst *command)
{
	int	err;

	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		err = redirect_files(command);
		/* Close unused side of the right pipe */
		close(r_pipe[READ]);
		/* Only write to right pipe if there was no output file */
		if (!command->outfile->name)
			if (dup2(r_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		close(r_pipe[WRITE]);
		/* Only read from left pipe if there was no input file */
		if (!command->infile->name)
			if (dup2(l_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		close(l_pipe[READ]);
		/* Execute command */
		if (err != -1)
		{
			test_built(command);
			if (data.built == 1)
			{
				execute_builtin(command);
				exit(data.exit_code);
			}
			else
				exec_cmd(command);
		}
		else
			exit(1);
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
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (-1);
	}
	if (command->index == 1)
	{
		if (first_command(right_pipe, command) == -1)
			return (-1);
	}
	else if (command->index == data.nb_of_commands)
	{
		if (last_command(left_pipe, right_pipe, command) == -1)
			return (-1);
	}
	else
	{
		if (inter_command(left_pipe, right_pipe, command) == -1)
			return (-1);
	}
	if (waitpid(-1, &command->status, 0) == -1)
		return (-1);
	if (WIFEXITED(command->status))
		data.exit_code = WEXITSTATUS(command->status);
	return (0);
}
