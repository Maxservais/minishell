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

	data.exit_code = 0;
	getcwd(current_path, sizeof(current_path));
	if (!commands->content[1])
		chdir(getenv("HOME"));
	else if (!ft_strncmp(commands->content[1], "\"\"", 2)) //en cas de cd "" il doit simplement retourner a la ligne
		rl_on_new_line();
	else if (!ft_strncmp(commands->content[1], "-", 1))
	{
		if (ft_strncmp(commands->content[1], "-L", 2)
			&& ft_strncmp(commands->content[1], "-P", 2))
		{
			error_usage("cd: ", commands->content[1], "cd: usage: cd [-L|-P] [dir]");
			commands->job_done = 1;
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(commands->content[1]) == -1)
	{
		error_cmd("bash: ", "cd: ", commands->content[1]);
		commands->job_done = 1;
		return (EXIT_FAILURE);
	}
	// need to unset first OLDPWD if there was one
	add_to_env(ft_strjoin("OLDPWD=", current_path));
	commands->job_done = 1;
	return (EXIT_SUCCESS);
}
