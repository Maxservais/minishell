#include "../minishell.h"

int	first_command(int right_pipe[], t_lst *command)
{
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		redirect_files(command);
		/* Close unused side of the right pipe */
		close(right_pipe[READ]);
		/* Only write to pipe if there was no output file */
		if (!command->outfile->name)
			if (dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		close(right_pipe[WRITE]);
		/* Execute command */
		execute_builtin(command); // A MODIFIER
		if (data.command_code != 0)
			if (exec_cmd(command) == -1)
				return (-1);
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
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		redirect_files(command);
		/* Only read from left pipe if there was no input file */
		if (!command->infile->name)
			if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		close(left_pipe[READ]);
		/* Execute command */
		execute_builtin(command);
		if (data.command_code != 0)
			if (exec_cmd(command) == -1)
				return (-1);
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
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file (if any), otherwise read from STDIN
		Write to last output file (if any), otherwise write to STDOUT */
		redirect_files(command);
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
		execute_builtin(command);
		if (data.command_code != 0)
			if (exec_cmd(command) == -1)
				return (-1);
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
			return (-1); // RETURN ERROR MESSAGE
	if (command->index == 1)
	{
		if (first_command(right_pipe, command) == -1)
			return (-1); // RETURN ERROR MESSAGE
	}
	else if (command->index == data.nb_of_commands)
	{
		if (last_command(left_pipe, right_pipe, command) == -1)
			return (-1); // RETURN ERROR MESSAGE
	}
	else
	{
		if (inter_command(left_pipe, right_pipe, command) == -1)
			return (-1); // RETURN ERROR MESSAGE
	}
	if (waitpid(-1, &command->status, 0) == -1)
		return (-1);
	return (0);
}
