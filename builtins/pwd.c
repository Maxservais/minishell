#include "../minishell.h"

void pwd(char **splited)
{
	char current_path[PATH_MAX];

	if (!ft_strncmp(splited[0], "pwd", 3))
		if (getcwd(current_path, sizeof(current_path)))
			printf("%s\n", current_path);
}
