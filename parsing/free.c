#include "../minishell.h"

void	free_splited(char **splited)
{
	int	x;

	x = 0;
	while (splited[x])
	{
		free(splited[x]);
		x++;
	}
	free(splited);
}

void	clean_all(t_token *tokens, char **splited, t_lst **commands)
{
	free(tokens);
	free_splited(splited);
	lstclear(commands);
}

void	free_envp(void)
{
	int	x;

	x = 0;
	while (g_data.envp[x])
	{
		free(g_data.envp[x]);
		x++;
	}
	free(g_data.envp);
}	
