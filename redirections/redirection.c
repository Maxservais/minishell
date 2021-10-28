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

int	open_files(void)
{
	int	i;
	
	i = 0;
	while (data.infile[i].name)
	{
		data.infile[i].fd = ft_open(data.infile[i].name, data.infile[i].mode);
		// printf("fd == %d\n", data.infile[i].fd);
		if (data.infile[i].fd == -1)
			return (-1);
		// if (param.fd1 == -1 || param.fd2 == -1)
		// 	perror("Error");
		i++;
	}
	i = 0;
	while (data.outfile[i].name)
	{
		data.outfile[i].fd = ft_open(data.outfile[i].name, data.outfile[i].mode);
		if (data.outfile[i].fd == -1)
			return (-1);
		// if (param.fd1 == -1 || param.fd2 == -1)
		// 	perror("Error");
		i++;
	}
	return (EXIT_SUCCESS);
}
