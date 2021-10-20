#include "../minishell.h"

/* chdir() changes the current working directory of the calling
process to the directory specified in path. */

static void	error_cd(char *str)
{
	ft_putstr_fd("cd: ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(str, 1);
}

int	cd(char **splited)
{
	// THIS CONDITION CAN BE REMOVED ONCE WE CHECK IN THE PARSING WHICH FUNCTION TO CALL
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

// LES ERREURS FAUT LES ECRIRE DANS LE STDOUT ET le STDERR? Ou juste STDOUT ?

/// CA DOIT UPDATER LE PWD de env
// CD doit etre capable de gerer les variables. 