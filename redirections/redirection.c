#include "../minishell.h"

int	open_file(char *file_name, int mode)
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
	return (fd);
}
