#include "../minishell.h"

void	add_files_loop(t_lst *commands, int *x, int *y, int *z)
{
	while (commands->content[(*x)])
	{
		if (!ft_strncmp(commands->content[(*x)], ">>", 2))
		{
			commands->outfile[(*z)].mode = 3;
			commands->outfile[(*z)++].name = commands->content[(*x) + 1];
		}
		else if (!ft_strncmp(commands->content[(*x)], ">", 1))
		{
			commands->outfile[(*z)].mode = 2;
			commands->outfile[(*z)++].name = commands->content[(*x) + 1];
		}
		else if (!ft_strncmp(commands->content[(*x)], "<<", 2))
		{
			commands->infile[(*y)].mode = 4;
			g_data.here_doc = 1;
			commands->infile[(*y)++].name = "/tmp/tmp";
		}
		else if (!ft_strncmp(commands->content[(*x)], "<", 1))
		{
			commands->infile[(*y)].mode = 1;
			commands->infile[(*y)++].name = commands->content[(*x) + 1];
		}
		(*x)++;
	}
}

int	add_files(t_lst *commands)
{
	int		nbr_ch;
	int		x;
	int		y;
	int		z;

	while (commands)
	{
		nbr_ch = count_chev(*commands, "<") + count_chev(*commands, "<<");
		commands->infile = malloc(sizeof(t_file) * (nbr_ch + 1));
		if (!commands->infile)
			return (-1);
		nbr_ch = count_chev(*commands, ">") + count_chev(*commands, ">>");
		commands->outfile = malloc(sizeof(t_file) * (nbr_ch + 1));
		if (!commands->outfile)
			return (-1);
		x = 0;
		y = 0;
		z = 0;
		add_files_loop(commands, &x, &y, &z);
		commands->infile[y].name = NULL;
		commands->outfile[z].name = NULL;
		commands = commands->next;
	}
	return (0);
}

int	redirect_input(int index, t_lst *commands)
{
	int	fd;

	if (index >= 0 && index == last_infile(commands))
	{
		fd = open("/tmp/tmp", O_RDONLY);
		if (fd < 0)
			return (-1);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (-1);
		close(fd);
	}
	else
	{
		if (dup2(commands->infile
				[last_infile(commands)].fd, STDIN_FILENO) == -1)
			return (-1);
		close(commands->infile[last_infile(commands)].fd);
	}
	return (0);
}

int	redirect_files(t_lst *commands)
{
	int	index;

	index = last_heredoc(commands);
	if (index != -1)
		heredoc(commands, index);
	if (commands->infile->name && commands->infile[last_infile(commands)].fd)
		if (redirect_input(index, commands) == -1)
			return (-1);
	if (commands->outfile->name
		&& commands->outfile[last_outfile(commands)].fd)
	{
		if (dup2(commands->outfile
				[last_outfile(commands)].fd, STDOUT_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (-1);
		}
		close(commands->outfile[last_outfile(commands)].fd);
	}
	return (0);
}

int	redirect_standard(t_lst *commands)
{
	if (commands->infile->name)
	{
		if (dup2(commands->save_stdin, STDIN_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (-1);
		}
		close(commands->save_stdin);
	}
	if (commands->outfile->name)
	{
		if (dup2(commands->save_stdout, STDOUT_FILENO) == -1)
		{
			ft_putendl_fd(strerror(errno), STDERR_FILENO);
			return (-1);
		}
		close(commands->save_stdout);
	}
	return (0);
}
