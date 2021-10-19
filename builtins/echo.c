#include "../minishell.h"

void	echo(char **splited, int word_count)
{
	int		x;

	if (!ft_strncmp(splited[0], "echo", 4) && ft_strncmp(splited[1], "-n", 2))
	{
		x = 1;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s\n", splited[x]);
	}
	if (!ft_strncmp(splited[0], ECHO, 4) && !ft_strncmp(splited[1], "-n", 2))
	{
		x = 2;
		while (splited[x] && x != word_count - 1)
			printf("%s ", splited[x++]);
		printf("%s", splited[x]);
	}
}
