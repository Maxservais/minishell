/* Reminders:
- retour des bonnes valeurs:
		0 en cas de succes
		1 en cas d'erreur (meme si partiellement reussi, si message d'erreur, renvoie 1)
- leaks to be found?
- Faut gerer export QQCHOSE+=qqchose !!!
- si export d'un truc qui existe deja, ca le remplace, ca n'ajoute pas un nouveau!!!!!!!!!!!!!

Some tests to run:
export coucou=hey=
------------------
declare -x coucou="hey="

export coucou=56 = hey=42
-------------------------
bash: export: `=': not a valid identifier
declare -x coucou="56"
declare -x hey="42"

export coucou=56 =
------------------------
bash: export: `=': not a valid identifier
declare -x coucou="56"

export = coucou=12
------------------
bash: export: `=': not a valid identifier
declare -x coucou="12"

export =
--------
bash: export: `=': not a valid identifier

export =coucou=hey
------------------
bash: export: `=coucou=hey': not a valid identifier

export "A= 2"
-------------
declare -x A=" 2"

export C=c B=b C=l
------------------
declare -x B="b"
declare -x C="l"

export "D C=c" B=b
------------------
bash: export: `D C=c': not a valid identifier
declare -x B="b"

*/

#include "../../minishell.h"

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
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	print_env(void)
{
	int		i;
	int		j;
	char	*var;
	char	*value;

	i = 0;
	while (data.envp[i] != NULL)
	{
		j = 0;
		while(data.envp[i][j])
		{
			if (data.envp[i][j] == '=')
			{
				var = ft_substr(data.envp[i], 0, j + 1);
				value = ft_substr(data.envp[i], j + 1, ft_strlen(data.envp[i]) - j);
				break ;
			}
			j++;
		}
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(var, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
		ft_putstr_fd(value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		free(var);
		free(value);
		i++;
	}
}

int	export(t_lst *commands)
{
	int		i;
	int		flag;
	char	*env;

	i = 0;
	flag = 0;
	if (!commands->cmd[1])
		print_env();
	else if (check_format(commands->cmd[1]) != -1)
	{
		env = strdup(commands->cmd[1]);
		if (!env)
			return (EXIT_FAILURE);
		// faut verifier que la variable existe pas deja, auquel cas faut la remplacer
		while (data.envp[i] != NULL)
		{
			if (!ft_strncmp(data.envp[i], env, check_format(env)))
			{
				data.envp[i] = env;
				printf("test: %s\n", data.envp[i]);
				flag = 1;
				break ;
			}
			i++;
		}
		if (flag != 1)
		{
			data.envp[i] = env;
			printf("env: %s\n", env);
			// how? Do I need to reallocate memory to fit the new addition?
			data.envp[i + 1] = NULL;
		}
		free(env);
	}
	else
	{
		if (!ft_strncmp(commands->cmd[1], "-", 1))
		{
			error_usage_export(commands->cmd[1]);
			return (EXIT_FAILURE);
		}
		else if (commands->cmd[2] && !check_format(commands->cmd[2]))
			error_args(commands->cmd[2]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
