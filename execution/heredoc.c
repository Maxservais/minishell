#include "../minishell.h"

int	last_heredoc(t_lst *command)
{
	int	x;

	x = 0;
	while (command->infile[x].name)
	{
		if (!ft_strcmp(command->infile[x].name, "/tmp/tmp"))
			return (x);
		x++;
	}
	return (-1);
}

int	heredoc_bis(int x, t_lst *commands, char *str, int fd)
{
	if (!ft_strncmp(commands->content[x], "<<", 2))
	{
		while (!str || ft_strcmp(str, commands->content[x + 1])
			|| !ft_strcmp(str, "\n"))
		{
			str = readline("> ");
			if (ft_strcmp(str, commands->content[x + 1])
				|| !ft_strcmp(str, "\n"))
			{
				write(fd, str, ft_strlen(str));
				write(fd, "\n", 1);
			}
			free(str);
		}
	}
	x++;
	return (x);
}

int	heredoc(t_lst *commands, int index)
{
	int		x;
	int		fd;
	int		res;
	char	*str;

	x = 0;
	res = -1;
	str = NULL;
	close(commands->infile[index].fd);
	fd = open("/tmp/tmp", O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sighandler_heredoc);
	while (commands->content[x])
		x = heredoc_bis(x, commands, str, fd);
	close(fd);
	return (0);
}
