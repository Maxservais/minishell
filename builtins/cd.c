#include "../minishell.h"

/* chdir() changes the current working directory of the calling
process to the directory specified in path. */

void	cd(char **splited)
{
	if (!ft_strncmp(splited[0], "cd", 2))
	{
		if (!splited[1])
		{
			if (chdir(getenv("HOME")) == -1)
				printf("cd: %s\n", strerror(errno));
			return ;
		}
		else
		{
			if (chdir(splited[1]) == -1)
			{
				printf("cd: %s: %s\n", strerror(errno), splited[1]);
				return ;
			}
		}
	}
}
