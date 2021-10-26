/* Reminders:
- retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
- variables d'environnement doivent etre passées au child process grace à execve.
Si j'export une variable, les enfants doivent en 'heriter'. Par contre l'inverse n'est pas vrai.
Ici je travaille directement sur environ, peut-etre qu'il faut travailler sur une copie.
*/

#include "../minishell.h"

static void	error_usage_export(char *str)
{
	char	*option;

	option = ft_substr(str, 0, 2);
	ft_putstr_fd("bash: export: ", STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("export: usage: export [-nf] [name[=value] ...] or export -p", STDERR_FILENO);
	free((void *)option);
}

static void	error_args(char *str)
{
	ft_putstr_fd("bash: export: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int check_format(char *str)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == '=')
			return (EXIT_SUCCESS);
		str++;
	}
	return (EXIT_FAILURE);
}

static void	print_env(void)
{
		int	i;

		i = 0;
		while (data.envp[i] != NULL)
		{
			ft_putstr_fd("declare -x ", STDIN_FILENO);
			ft_putendl_fd(data.envp[i], STDIN_FILENO);
			i++;
		}
}

int	export(t_lst *commands)
{
	int			i;
	char		*env;

	i = 0;
	if (!commands->content[1])
		print_env();
	else if (!check_format(commands->content[1]))
	{
		env = strdup(commands->content[1]);
		if (!env)
			return (EXIT_FAILURE);
		while (data.envp[i] != NULL)
			i++;
		data.envp[i] = env;
		data.envp[i + 1] = NULL;
	}
	else
	{
		if (!ft_strncmp(commands->content[1], "-", 1))
			error_usage_export(commands->content[1]);
		else if (commands->content[2] && !check_format(commands->content[2]))
			error_args(commands->content[2]);
		return (EXIT_FAILURE);
	}
	commands->job_done = 1;
	return (EXIT_SUCCESS);
}
