/* Reminders:
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

#include "../../minishell.h"

static void	add_to_env(char *variable)
{
	int			i;

	i = 0;
	while (data.envp[i] != NULL)
			i++;
	data.envp[i] = variable;
	data.envp[i + 1] = NULL;
}

int	cd(t_lst *commands)
{
	char	current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));
	if (!commands->cmd[1])
		chdir(getenv("HOME"));
	else if (!ft_strcmp(commands->cmd[1], "\0"))
		return (EXIT_SUCCESS);
	else if (!ft_strncmp(commands->cmd[1], "-", 1))
	{
		if (ft_strcmp(commands->cmd[1], "-L")
			&& ft_strcmp(commands->cmd[1], "-P"))
		{
			error_usage("cd: ", commands->cmd[1], "cd: usage: cd [-L|-P] [dir]");
			return (EXIT_FAILURE);
		}
		else
			chdir(commands->cmd[2]);
	}
	else if (chdir(commands->cmd[1]) == -1)
	{
		error_cmd("bash: ", "cd: ", commands->cmd[1]);
		return (EXIT_FAILURE);
	}
	// need to unset first OLDPWD if there was one
	add_to_env(ft_strjoin("OLDPWD=", current_path));
	return (EXIT_SUCCESS);
}
