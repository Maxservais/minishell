/* Reminders:
- Condition to check whether command is 'export' or not can be removed
once we check in the parsing which function should be called (cd, pwd, echo, etc.).
- variables d'environnement doivent etre passées au child process grace à execve.
Si j'export une variable, les enfants doivent en 'heriter'. Par contre l'inverse n'est pas vrai.
Ici je travaille directement sur environ, peut-etre qu'il faut travailler sur une copie.
*/

#include "../minishell.h"

static void	error_usage(char *str)
{
	char	*err;

	err = ft_substr(str, 0, 2);
	ft_putstr_fd("bash: export: ", STDERR_FILENO);
	ft_putstr_fd(err, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("export: usage: export [-nf] [name[=value] ...] or export -p", STDERR_FILENO);
	free((void *)err);
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

static void	print_env(char **environ)
{
		int	i;

		i = 0;
		while (environ[i] != NULL)
		{
			ft_putstr_fd("declare -x ", STDIN_FILENO);
			ft_putendl_fd(environ[i], STDIN_FILENO);
			i++;
		}
}

// !!!!!!!! retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
int	export(char **splited)
{
	int			i;
	char		*env;
	extern char	**environ;

	if (!ft_strncmp(splited[0], "export", 6))
	{
		i = 0;
		if (!splited[1])
			print_env(environ);
		else if (!check_format(splited[1]))
		{
			env = strdup(splited[1]);
			if (!env)
				return (EXIT_FAILURE);
			while (environ[i] != NULL)
				i++;
			environ[i] = env;
			environ[i + 1] = NULL;
		}
		else
		{
			if (!ft_strncmp(splited[1], "-", 1))
				error_usage(splited[1]);
			else if (splited[2] && !check_format(splited[2]))
				error_args(splited[2]);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
