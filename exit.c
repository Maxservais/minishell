#include "pipex.h"

void	ft_exit(char **splited, int *exit)
{
	if (!ft_strncmp(splited[0], "exit", 5))
		*exit = 1;
}
