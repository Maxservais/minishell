#include "../minishell.h"

void	add_files(t_lst *commands)
{
	int		nbr_chevrons;
	int		x;
	int		y;
	int		z;

	while (commands)
	{
		nbr_chevrons = count_chevrons(*commands, "<");
		commands->infile = malloc(sizeof(t_file) * (nbr_chevrons + 1));
		nbr_chevrons = count_chevrons(*commands, ">") + count_chevrons(*commands, ">>");
		commands->outfile = malloc(sizeof(t_file) * (nbr_chevrons + 1));
		x = 0;
		y = 0;
		z = 0;
		while (commands->content[x])
		{
			if (!ft_strncmp(commands->content[x], ">>", 2))
			{
				commands->outfile[z].mode = 3;
				commands->outfile[z++].name = commands->content[x + 1];
			}
			else if (!ft_strncmp(commands->content[x], ">", 1))
			{
				commands->outfile[z].mode = 2;
				commands->outfile[z++].name = commands->content[x + 1];
			}
			else if (!ft_strncmp(commands->content[x], "<", 1))
			{
				commands->infile[y].mode = 1;
				commands->infile[y++].name = commands->content[x + 1];
			}
			x++;
		}
		commands->infile[y].name = NULL;
		commands->outfile[z].name = NULL;
		commands = commands->next;
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
	else if (mode == 2)
	{
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (-1);
	}
	else
	{
		fd = open(file_name, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd < 0)
			return (-1);
	}
	return (fd);
}

int	open_files(t_lst *commands)
{
	int		i;

	while (commands)
	{
		i = 0;
		while (commands->infile[i].name)
		{
			commands->infile[i].fd = ft_open(commands->infile[i].name, commands->infile[i].mode);
			if (commands->infile[i].fd == -1)
				return (-1);
			// GERER LES ERREURS !!!!!!!!!!!!!!!!
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
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
}

int	redirect_files(t_lst *commands)
{
	// heredoc(commands);
	if (commands->infile->name && commands->infile[last_infile(commands)].fd)
	{
		// Bug ici: commands->infile->name devient EOF qd on a un heredoc
		printf("file name: %s\n", commands->infile->name);
		if (dup2(commands->infile[last_infile(commands)].fd, STDIN_FILENO) == -1)
		{
			printf("COUCOU2\n");
			return (-1);
		}
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

int	heredoc(t_lst *commands)
{
	int		x;
	int		res;
	int		fd;
	char	*str;

	x = 0;
	res = -1;
	fd = open("tmp_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (res);
	str = NULL;
	// Ajouter la gestion des signaux ici!
	while (commands->content[x])
	{
		if (!ft_strncmp(commands->content[x], "<<", 2))
		{
			while (!str || ft_strncmp(str, commands->content[x + 1],
				ft_strlen(commands->content[x + 1])))
			{
				str = readline("> ");
				write(fd, str, ft_strlen(str));
				write(fd, "\n", 1);
				free(str);
			}
		}
		x++;
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	// unlink("tmp_file");
	return (0);
}