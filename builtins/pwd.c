#include "../minishell.h"

void pwd(char **splited)
{
	char pwd[PATH_MAX];

	if (!ft_strncmp(splited[0], "pwd", 3) && getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
}
