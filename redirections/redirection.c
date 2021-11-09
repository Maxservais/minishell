#include "../minishell.h"

int	ft_open(char *file_name, int mode)
{
	int	fd;

	if (mode == 1)
	{
		fd = open(file_name, O_RDONLY);
		if (fd < 0)
			return (-1);
	}
	else
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
	}
	// Ajouter 3eme mode pour fichier 'append'
	return (fd);
}

int	open_files(t_lst *commands)
{
	int		i;
	t_lst	*trav;
	
	i = 0;
	trav = commands;
	while (trav)
	{
		while (commands->infile[i].name)
		{
			commands->infile[i].fd = ft_open(commands->infile[i].name, commands->infile[i].mode);
			if (commands->infile[i].fd == -1)
				return (-1);
			// if (param.fd1 == -1 || param.fd2 == -1)
			// 	perror("Error");
			i++;
		}
		i = 0;
		while (commands->outfile[i].name)
		{
			commands->outfile[i].fd = ft_open(commands->outfile[i].name, commands->outfile[i].mode);
			if (commands->outfile[i].fd == -1)
				return (-1);
			// if (param.fd1 == -1 || param.fd2 == -1)
			// 	perror("Error");
			i++;
		}
		trav = trav->next;
	}
	return (EXIT_SUCCESS);
}
