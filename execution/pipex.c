/* Il faut check avant d'executer une commande si on est face à un built-in ou non */

#include "../minishell.h"

int	first_command(int right_pipe[], t_lst *command)
{
	command->pid = fork();
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		/* Read from last input file if there is one, otherwise read from STDIN */
		if (command->infile->name && command->infile[last_infile(command)].fd)
		{
			if (dup2(command->infile[last_infile(command)].fd, STDIN_FILENO) == -1)
				return (-1);
			close(command->infile[last_infile(command)].fd);
		}
		/* Write to last output file if there is one, otherwise write to STDOUT */
		if (command->outfile->name && command->outfile[last_outfile(command)].fd)
		{
			if (dup2(command->outfile[last_outfile(command)].fd, STDOUT_FILENO) == -1)
				return (-1);
			close(command->outfile[last_outfile(command)].fd);
		}
		if (close(right_pipe[READ]) == -1)
				return (-1);
		/* Only write to pipe if there was no output file */
		if (!command->outfile->name)
			if (dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		execute_builtin(command);
		if (data.command_code != 0)
		{
			if (exec_cmd(command) == -1)
				return (-1);
		}
	}
	else
	{
		if (waitpid(-1, &command->status, 0) == -1)
			return (-1);
		if (close(right_pipe[WRITE]) == -1)
			return (-1);
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
		/* Only read from pipe if there was no input file */
		if (!command->infile->name)
		{
			if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		}
		else
			close(left_pipe[READ]);
		if (close(left_pipe[WRITE]) == -1)
			return (-1);
		/* Read from last input file if there is one, otherwise read from pipe */
		if (command->infile->name && command->infile[1].fd)
		{
			if (dup2(command->infile[last_infile(command)].fd, STDIN_FILENO) == -1)
				return (-1);
			close(command->infile[last_infile(command)].fd);
		}
		/* Write to last output file if there is one, otherwise write to STDOUT */
		if (command->outfile->name && command->outfile[last_outfile(command)].fd)
		{
			if (dup2(command->outfile[last_outfile(command)].fd, STDOUT_FILENO) == -1)
				return (-1);
			close(command->outfile[last_outfile(command)].fd);
		}
		execute_builtin(command);
		if (data.command_code != 0)
		{
			if (exec_cmd(command) == -1)
				return (-1);
		}
	}
	else
	{
		if (waitpid(-1, &command->status, 0) == -1)
			return (-1);
		if (close(right_pipe[READ]) == -1 || close(right_pipe[WRITE]) == -1)
			return (-1);
		if (close(left_pipe[READ]) == -1)
			return (-1);
		return (0);
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
		if (close(r_pipe[READ]) == -1 || dup2(l_pipe[READ], STDIN_FILENO) == -1)
			return (-1);
		if (dup2(r_pipe[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		if (exec_cmd(command) == -1)
			return (-1);
	}
	else
	{
		if (waitpid(-1, &command->status, 0) == -1)
			return (-1);
		if (close(r_pipe[WRITE]) == -1)
			return (-1);
		if (close(l_pipe[READ]) == -1)
			return (-1);
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
	// Not sure it's the right place here
	redirect_standard(command);
	return (0);
}
