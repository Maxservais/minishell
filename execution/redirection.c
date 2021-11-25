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
				if (ft_strlen(trav->content[x]) == 1)
					trav->infile[y++].name = trav->content[x + 1];
				else
					trav->infile[y++].name = trav->content[x] + 1;
			}
			if (!ft_strncmp(trav->content[x], ">", 1))
			{
				trav->outfile[z].mode = 2;
				if (ft_strlen(trav->content[x]) == 1)
					trav->outfile[z++].name = trav->content[x + 1];
				else
					trav->outfile[z++].name = trav->content[x] + 1;
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
	
	trav = commands; // TRAV IS A BIT UNNECCESSARY
	while (trav)
	{
		i = 0;
		while (trav->infile[i].name)
		{
			trav->infile[i].fd = ft_open(trav->infile[i].name, trav->infile[i].mode);
			if (trav->infile[i].fd == -1)
				return (-1);
			// GERER LES ERREURS !!!!!!!!!!!!!!!!
			// if (param.fd1 == -1 || param.fd2 == -1) 
			// 	perror("Error");
			i++;
		}
		i = 0;
		while (trav->outfile[i].name)
		{
			trav->outfile[i].fd = ft_open(trav->outfile[i].name, trav->outfile[i].mode);
			if (trav->outfile[i].fd == -1)
				return (-1);
			// if (param.fd1 == -1 || param.fd2 == -1)
			// 	perror("Error");
			i++;
		}
		trav = trav->next;
	}
	return (EXIT_SUCCESS);
}

int	redirect_files(t_lst *commands)
{
	if (commands->infile->name && commands->infile[last_infile(commands)].fd)
	{
		if (dup2(commands->infile[last_infile(commands)].fd, STDIN_FILENO) == -1)
			return (-1);
		close(commands->infile[last_infile(commands)].fd);
	}
	if (commands->outfile->name && commands->outfile[last_outfile(commands)].fd)
	{
		if (dup2(commands->outfile[last_outfile(commands)].fd, STDOUT_FILENO) == -1)
			return (-1);
		close(commands->outfile[last_outfile(commands)].fd);
	}
	return (0);
}

int	redirect_standard(t_lst *commands)
{
	if (commands->infile->name)
	{
		if (dup2(commands->save_stdin, STDIN_FILENO) == -1)
			return (-1);
		close(commands->save_stdin);
	}
	if (commands->outfile->name)
	{
		if (dup2(commands->save_stdout, STDOUT_FILENO) == -1)
			return (-1);
		close(commands->save_stdout);
	}
	return (0);
}

