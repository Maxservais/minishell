#include "../minishell.h"

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

void		execute_builtin(t_lst *commands)
{
	// IL FAUT GERER LES REDIRECTIONS!!!!
	test_built(commands);
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

void	handle_command(t_lst *commands)
{
	data.command_code = -1;
	commands->save_stdin = dup(STDIN_FILENO);
	commands->save_stdout = dup(STDOUT_FILENO);
	open_files(commands);
	if (!ft_strcmp(commands->content[0], "top"))
		signal(SIGINT, sighandler_cmd1);
	else
		signal(SIGINT, sighandler_cmd);
	signal(SIGQUIT, sighandler_cmd);
	if (data.nb_of_commands == 1)
	{
		execute_builtin(commands);
		if (data.command_code != 0)
		{
			//printf("command = %s\n",commands->content[0]);
			commands->pid = fork();
			if (commands->pid < 0)
				return ; // RETURN ERROR
			else if (commands->pid == 0)
			{
				// if input files, redirect
				if (commands->infile->name && commands->infile[last_infile(commands)].fd)
				{
					if (dup2(commands->infile[last_infile(commands)].fd, STDIN_FILENO) == -1)
						return ;
					close(commands->infile[last_infile(commands)].fd);
				}
				// if output files, redirect
				if (commands->outfile->name && commands->outfile[last_outfile(commands)].fd)
				{
					if (dup2(commands->outfile[last_outfile(commands)].fd, STDOUT_FILENO) == -1)
						return ;
					close(commands->outfile[last_outfile(commands)].fd);
				}
				// Execute command
				if (exec_cmd(commands) == -1)
				{
					return ;
				}
			}
			else									// CHANGEMENT ICIIIIIIIIII
			{
				wait(&commands->status);
				if (commands->status == 256)
				{
					data.exit_code = 1;
					return ;
				}
				else if (commands->status < 256)
				{
					data.exit_code = 0;
					return ;
				}
				// if (waitpid(-1, &commands->status, 0) == -1)
				// 	return ;
			}
		}
		if (commands->status > 256 && data.built == 0)
		{
			write(2, "bash: ", 6);
			write(2, commands->content[0], ft_strlen(commands->content[0]));
			write(2, ": command not found\n", 20);
			data.exit_code = 127;
		}
		// if (handle_one_command(commands) == -1)
		// 	return ; // report error
	}
	else
	{
		if (pipex(commands, STDIN_FILENO) == -1)
			return ; // report error
	}
}

int	handle_one_command(t_lst *commands)
{
	if (redirect_files(commands) == -1)
		return (-1); // GERER ERREUR
	execute_builtin(commands);
	if (data.command_code == 0)
		redirect_standard(commands);
	else
	{
		commands->pid = fork();
		if (commands->pid < 0)
			return (-1); // GERER ERREUR
		else if (commands->pid == 0)
		{
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
	}
	return (0);
}
