#include "../minishell.h"

void	add_files(t_lst **commands)
{
	t_lst	*trav;
	int		x;
	int		y;
	int		z;

	trav = *commands;
	while (trav)
	{
		trav->infile = malloc(sizeof(t_file) * (count_chevrons(*trav, '<') + 1));
		trav->outfile = malloc(sizeof(t_file) * (count_chevrons(*trav, '>') + 1));
		x = 0;
		y = 0;
		z = 0;
		while (trav->content[x])
		{
			if (!ft_strncmp(trav->content[x], "<", 1))
			{
				trav->infile[y].mode = 1;
				trav->infile[y++].name = trav->content[x + 1];
			}
			if (!ft_strncmp(trav->content[x], ">", 1))
			{
				trav->outfile[z].mode = 2;
				trav->outfile[z++].name = trav->content[x + 1];
			}
			x++;
		}
		trav->infile[y].name = NULL;
		trav->outfile[z].name = NULL;
		trav = trav->next;
	}
}

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
