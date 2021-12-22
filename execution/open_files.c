#include "../minishell.h"

int	ft_open(char *file_name, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(file_name, O_RDONLY);
	else if (mode == 2)
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (mode == 3)
		fd = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	open_files(t_lst *commands)
{
	int	i;

	while (commands)
	{
		i = 0;
		while (commands->infile[i].name)
		{
			commands->infile[i].fd
				= ft_open(commands->infile[i].name, commands->infile[i].mode);
			if (commands->infile[i].fd == -1)
				return (invalid_file(commands, i));
			i++;
		}
		i = 0;
		while (commands->outfile[i].name)
		{
			commands->outfile[i].fd
				= ft_open(commands->outfile[i].name, commands->outfile[i].mode);
			if (commands->outfile[i].fd == -1)
				return (-1);
			i++;
		}
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
}

int	close_files(t_lst *commands)
{
	int	i;

	while (commands)
	{
		i = 0;
		while (commands->infile[i].name && commands->infile[i].fd != -1)
		{
			close(commands->infile[i].fd);
			i++;
		}
		i = 0;
		while (commands->outfile[i].name && commands->outfile[i].fd != -1)
		{
			close(commands->outfile[i].fd);
			i++;
		}
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
}
