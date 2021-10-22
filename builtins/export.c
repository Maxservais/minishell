/* Reminders:
- Condition to check whether command is 'export' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
- variables d'environnement doivent etre passées au child process grace à execve.
*/

#include "../minishell.h"

void	export(char **splited)
{
	if (!ft_strncmp(splited[0], "export", 6))
	{
		int			i;
		char		*env;
		extern char	**environ;

		i = 0;
		if (splited[1])
		{
			// avant d'export, je dois check que j'ai bien format key=value
			env = strdup(splited[1]);
			// protect
			while (environ[i] != NULL)
				i++;
			environ[i] = env;
			i++;
			environ[i] = NULL;
		}
		else
		{
			while (environ[i] != NULL)
			{
				ft_putendl_fd(environ[i], STDIN_FILENO);
				i++;
			}
		}
		// ajouter gestion d'erreur!!!

		// retour des bonnes valeurs (0 en cas de succes, etc.)

	}
}
