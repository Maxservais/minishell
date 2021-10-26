#include "../minishell.h"

int	ft_open(char *file_name, int mode)
{
	int	fd;

	if (mode == 0)
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

int	open_files(char **files)
{
	int	i;
	int	mode;

	// On ouvre tous les fichiers d'input et d'output
	// param.fd1 = open_file(argv[1], 0);
	// param.fd2 = open_file(argv[argc - 1], 1);
	// if (param.fd1 == -1 || param.fd2 == -1)
	// 	perror("Error");
	i = 0;
	while (files[i])
	{
		if (ft_open(files[i], mode) == -1)
			return (-1);
		i++;
	}
	return (EXIT_SUCCESS);
}
