/* Reminders:
- Condition to check whether command is 'cd' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
- La commande 'cd' doit etre capable de gerer les variables qui ont été EXPORT.
e.g. export test=Documents/minishell cd $test
- the 'cd' command should update the PWD environment variable and create the OLDPWD env variable.
e.g	bash-3.2$ env | grep PWD
	PWD=/Users/mservais/Documents/minishell
	bash-3.2$ cd pipex/
	bash-3.2$ env | grep PWD
	PWD=/Users/mservais/Documents/minishell/pipex
	OLDPWD=/Users/mservais/Documents/minishell
*/

#include "../minishell.h"

static void	error_cd(char *str)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

int	cd(char **splited)
{
	if (!ft_strncmp(splited[0], "cd", 2)) 
	{
		if (!splited[1])
		{
			if (chdir(getenv("HOME")) == -1)
			{
				error_cd("HOME");
				return (EXIT_FAILURE);
			}
		}
		else
		{
			if (chdir(splited[1]) == -1)
			{
				error_cd(splited[1]);
				return (EXIT_FAILURE);
			}
		}
	}
	return (EXIT_SUCCESS);
}
