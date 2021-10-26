#include "pipex.h"

int	first_command(char **envp, int right_pipe[], t_param *param)
{
	param->pid = fork();
	if (param->pid < 0)
		return (-1);
	else if (param->pid == 0)
	{
		if (close(right_pipe[READ]) == -1
			|| dup2(param->fd1, STDIN_FILENO) == -1)
			return (-1);
		if (close(param->fd1) == -1
			|| dup2(right_pipe[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		if (exec_cmd(param->cmds[param->pos], envp) == -1)
			return (-1);
	}
	else
	{
		if (waitpid(-1, &param->status, 0) == -1)
			return (-1);
		if (close(right_pipe[WRITE]) == -1)
			return (-1);
		param->pos++;
		if (pipex(envp, param, right_pipe) == -1)
			return (-1);
	}
	return (0);
}

int	last_command(char **envp, int left_pipe[], int right_pipe[], t_param *param)
{
	param->pid = fork();
	if (param->pid < 0)
		return (-1);
	else if (param->pid == 0)
	{
		if (close(left_pipe[WRITE]) == -1
			|| dup2(param->fd2, STDOUT_FILENO) == -1)
			return (-1);
		if (close(param->fd2) == -1
			|| dup2(left_pipe[READ], STDIN_FILENO) == -1)
			return (-1);
		if (exec_cmd(param->cmds[param->pos], envp) == -1)
			return (-1);
	}
	else
	{
		if (waitpid(-1, &param->status, 0) == -1)
			return (-1);
		if (close(right_pipe[READ]) == -1 || close(right_pipe[WRITE]) == -1)
			return (-1);
		if (close(left_pipe[READ]) == -1)
			return (-1);
		return (0);
	}
	return (0);
}

int	inter_command(char **envp, int l_pipe[], int r_pipe[], t_param *p)
{
	p->pid = fork();
	if (p->pid < 0)
		return (-1);
	else if (p->pid == 0)
	{
		if (close(r_pipe[READ]) == -1 || dup2(l_pipe[READ], STDIN_FILENO) == -1)
			return (-1);
		if (dup2(r_pipe[WRITE], STDOUT_FILENO) == -1)
			return (-1);
		if (exec_cmd(p->cmds[p->pos], envp) == -1)
			return (-1);
	}
	else
	{
		if (waitpid(-1, &p->status, 0) == -1)
			return (-1);
		if (close(r_pipe[WRITE]) == -1)
			return (-1);
		if (close(l_pipe[READ]) == -1)
			return (-1);
		p->pos++;
		if (pipex(envp, p, r_pipe) == -1)
			return (-1);
	}
	return (0);
}

int	pipex(char **envp, t_param *param, int left_pipe[])
{
	int		right_pipe[2];

	if (pipe(right_pipe) == -1)
		return (report_error());
	if (param->pos == 0)
	{
		if (first_command(envp, right_pipe, param) == -1)
			return (report_error());
	}
	else if (param->cmds[param->pos + 1] == NULL)
	{
		if (last_command(envp, left_pipe, right_pipe, param) == -1)
			return (report_error());
	}
	else
	{
		if (inter_command(envp, left_pipe, right_pipe, param) == -1)
			return (report_error());
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_param	param;

	if (argc != 5)
		return (ft_err_return(ERROR_USAGE));
	param.fd1 = open_file(argv[1], 0);
	param.fd2 = open_file(argv[argc - 1], 1);
	if (param.fd1 == -1 || param.fd2 == -1)
		perror("Error");
	param.cmds = malloc(sizeof(char **) * argc - 1);
	if (!param.cmds)
		return (EXIT_FAILURE);
	i = 2;
	while (i < argc - 1)
	{
		param.cmds[i - 2] = ft_split(argv[i], ' ');
		if (!param.cmds[i - 2])
			return (ft_free(param.cmds));
		i++;
	}
	param.cmds[i - 2] = NULL;
	if (pipex(envp, &param, STDIN_FILENO) == -1)
		return (ft_free(param.cmds));
	return (EXIT_SUCCESS);
}
