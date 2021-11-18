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
		/* Close unused side of the right pipe */
		if (close(right_pipe[READ]) == -1)
			return (-1);
		/* Only write to pipe if there was no output file */
		if (!command->outfile->name)
		{
			// close(STDOUT_FILENO);
			if (dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
				return (-1);
		}
		else
		{
			if (close(right_pipe[WRITE]) == -1)
				return (-1);
		}
		// if (!command->infile->name)
		// {
		// 	if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
		// 		return (-1);
		// }
		/* Execute command */
		execute_builtin(command);
		if (data.command_code != 0)
		{
			if (exec_cmd(command) == -1)
				return (-1);
		}
	}
	else
	{
		if (waitpid(-1, &command->status, 0) == -1) // DO I NEED TO WAIT FOR ALL CHILD PROCESSES? OR SPECIFY THE PID?
			return (-1);
		// if (redirect_standard(command) == -1)
		// 		return (-1); // GERER ERREUR
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
		/* Close unused side of the left pipe */
		if (close(left_pipe[WRITE]) == -1)
			return (-1);
		/* Only read from left pipe if there was no input file */
		if (!command->infile->name)
		{
			if (dup2(left_pipe[READ], STDIN_FILENO) == -1)
				return (-1);
		}
		else
			close(left_pipe[READ]);
		/* Read from last input file if there is one, otherwise read from pipe */
		if (command->infile->name && command->infile[last_infile(command)].fd)
		{
			// close(STDIN_FILENO);
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
		/* Execute command */
		execute_builtin(command);
		if (data.command_code != 0)
		{
			if (exec_cmd(command) == -1)
				return (-1);
		}
	}
	else
	{
		if (close(right_pipe[READ]) == -1 || close(right_pipe[WRITE]) == -1)
			return (-1);
		if (waitpid(-1, &command->status, 0) == -1)
			return (-1);
		if (close(left_pipe[READ]) == -1)
			return (-1);
	}
	return (0);
}

// int	inter_command(int l_pipe[], int r_pipe[], t_lst *command)
// {
// 	command->pid = fork();
// 	if (command->pid < 0)
// 		return (-1);
// 	else if (command->pid == 0)
// 	{
// 		/* Read from last input file if there is one, otherwise read from STDIN */
// 		if (command->infile->name && command->infile[last_infile(command)].fd)
// 		{
// 			if (dup2(command->infile[last_infile(command)].fd, STDIN_FILENO) == -1)
// 				return (-1);
// 			close(command->infile[last_infile(command)].fd);
// 		}
// 		/* Write to last output file if there is one, otherwise write to STDOUT */
// 		if (command->outfile->name && command->outfile[last_outfile(command)].fd)
// 		{
// 			if (dup2(command->outfile[last_outfile(command)].fd, STDOUT_FILENO) == -1)
// 				return (-1);
// 			close(command->outfile[last_outfile(command)].fd);
// 		}
// 		/* Close unused side of the left pipe */
// 		if (close(l_pipe[WRITE]) == -1)
// 			return (-1);
// 		/* Only read from left pipe if there was no input file */
// 		if (!command->infile->name)
// 		{
// 			if (dup2(l_pipe[READ], STDIN_FILENO) == -1)
// 				return (-1);
// 		}
// 		else
// 			close(l_pipe[READ]); // JE LE FERME AUSSI DANS LE PARENT PROCESS, EST-CE QUE C'EST GRAVE?
		
		
		
		
// 		/* Close unused side of the right pipe */
// 		if (close(r_pipe[READ]) == -1)
// 			return (-1);
// 		/* Only write to right pipe if there was no output file */
// 		if (!command->outfile->name)
// 		{
// 			if (dup2(r_pipe[WRITE], STDOUT_FILENO) == -1)
// 				return (-1);
// 		}
// 		else
// 			close(r_pipe[WRITE]);
// 		/* Execute command */
// 		execute_builtin(command);
// 		if (data.command_code != 0)
// 		{
// 			if (exec_cmd(command) == -1)
// 				return (-1);
// 		}
// 	}
// 	else
// 	{
// 		if (waitpid(-1, &command->status, 0) == -1)
// 			return (-1);
// 		if (!command->outfile->name)
// 		{
// 			if (close(r_pipe[WRITE]) == -1)
// 				return (-1);
// 		}
// 		if (!command->infile->name)
// 		{
// 			if (close(l_pipe[READ]) == -1)
// 				return (-1);
// 		}
// 		if (pipex(command->next, r_pipe) == -1)
// 			return (-1);
// 	}
// 	return (0);
// }

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
	// else
	// {
	// 	if (inter_command(left_pipe, right_pipe, command) == -1)
	// 		return (-1); // RETURN ERROR MESSAGE
	// }
	return (0);
}
