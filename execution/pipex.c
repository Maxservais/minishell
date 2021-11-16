/* Il faut check avant d'executer une commande si on est face à un built-in ou non */

#include "../minishell.h"

int	first_command(int right_pipe[], t_lst *command)
{
	command->pid = fork();
	if (command->infile[0].fd)
		command->infile[0].fd = STDIN_FILENO;
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		if (close(right_pipe[READ]) == -1
			|| dup2(command->infile[0].fd, STDIN_FILENO) == -1)
				return (-1);
		if (close(command->infile[0].fd) == -1
			|| dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		if (exec_cmd(command) == -1)
			return (-1);
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
	wait(&data.exit_code);
	if (WIFSIGNALED(data.exit_code))
		data.exit_code = 128 + WTERMSIG(data.exit_code);
	return (0);
}

int	last_command(int left_pipe[], int right_pipe[], t_lst *command)
{
	command->pid = fork();
	if (command->outfile[0].fd)
		command->outfile[0].fd = STDOUT_FILENO;
	if (command->pid < 0)
		return (-1);
	else if (command->pid == 0)
	{
		if (close(left_pipe[WRITE]) == -1
			|| dup2(command->outfile[0].fd, STDOUT_FILENO) == -1)
			return (-1);
		if (close(command->outfile[0].fd) == -1
			|| dup2(left_pipe[READ], STDIN_FILENO) == -1)
			return (-1);
		if (exec_cmd(command) == -1)
			return (-1);
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
	return (0);
}