/* Reminders:
- retour des bonnes valeurs (0 en cas de succes, etc.) !!!!!!!!!
- variables d'environnement doivent etre passées au child process grace à execve.
Si j'export une variable, les enfants doivent en 'heriter'. Par contre l'inverse n'est pas vrai.
Ici je travaille directement sur environ, peut-etre qu'il faut travailler sur une copie.
- leaks to be found
- export coucou=hey = bonjour=y a gerer!!! Il faut renvoyer erreur mais qd meme
- Faut gerer export QQCHOSE+=qqchose !!!
- si export d'un truc qui existe deja, ca le remplace, ca n'ajoute pas un nouveau

Some tests to run:
export coucou=hey=
export coucou=56 = hey=42
export coucou=56 =
export = coucou=12
export =
export bonjour=bon = holla=56
export =coucou=hey
export "A= 2"
export C=c CWI=2
export C=c B=b C=l
export " C=c"
export "D C=c"
export "D C=c" B=b
*/

#include "../../minishell.h"

// static void	error_usage_export(char *str)
// {
// 	char	*option;

// 	option = ft_substr(str, 0, 2);
// 	ft_putstr_fd("bash: export: ", STDERR_FILENO);
// 	ft_putstr_fd(option, STDERR_FILENO);
// 	ft_putendl_fd(": invalid option", STDERR_FILENO);
// 	ft_putendl_fd("export: usage: export [-nf] [name[=value] ...] or export -p", STDERR_FILENO);
// 	free((void *)option);
// }

static void	error_args(char *str)
{
	ft_putstr_fd("bash: export: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int find_equal_c(char *str)
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
	int	i;

	i = 0;
	while (g_data.envp[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDIN_FILENO);
		ft_putendl_fd(g_data.envp[i], STDIN_FILENO);
		i++;
	}
}

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] == '=')
				return (i - 1);
		}
		else
			i++;
	}
	return (-1);
}

char	*append_char(char *str, char *str_before)
{
	int		index_plus;
	int		index_equal;
	char	*key;
	char	*value;
	char	*to_append;
	char	*tmp1;
	char	*tmp2;
	char	*final;
	char	c;

	c = '=';
	index_plus = find_plus(str);
	key = ft_substr(str, 0, index_plus);
	index_equal = find_equal_c(str_before);
	value = ft_substr(str_before, index_equal + 1, ft_strlen(str_before) - index_equal);
	index_equal = find_equal_c(str);
	to_append = ft_substr(str, index_equal + 1, ft_strlen(str) - index_equal);
	tmp1 = ft_strjoin(value, to_append);
	tmp2 = ft_strjoin(key, &c);
	final = ft_strjoin(tmp2, tmp1);
	free(key);
	free(value);
	free(to_append);
	free(tmp1);
	free(tmp2);
	return (final);
}

static int	exported(char *str)
{
	int		i;
	int		plus;
	int		equal;
	char	*key_str;
	char	*key_envp;
	char	*tmp;

	i = 0;
	plus = find_plus(str);
	equal = find_equal_c(str);
	if (plus != -1)
		equal = plus;
	key_str = ft_substr(str, 0, equal);
	while (g_data.envp[i])
	{
		tmp = ft_strdup(g_data.envp[i]);
		key_envp = ft_substr(g_data.envp[i], 0, find_equal_c(g_data.envp[i]));
		if (!ft_strcmp_parse(key_str, key_envp, ft_strlen(key_str)))
		{
			free(g_data.envp[i]);
			if (plus != -1)
				g_data.envp[i] = append_char(str, g_data.envp[i]);
			else
				g_data.envp[i] = ft_strdup(str);
			free(tmp);
			free(key_str);
			free(key_envp);
			return (i);
		}
		free(tmp);
		free(key_envp);
		i++;
	}
	free(key_str);
	return (-1);
}


int	export(t_lst *commands)
{
	int		i;
	int		ret;

	if (!commands->cmd[1])
	{
		print_env();
		g_data.exit_code = 0;
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (commands->cmd[i])
	{
		ret = 0;
		if (commands->cmd[i][0] == '=' || ft_isdigit(commands->cmd[i][0]))
			error_args(commands->cmd[i]);
		else if (find_equal_c(commands->cmd[i]) != -1)
		{
			if (exported(commands->cmd[i]) >= 0)
				ret = 1;
			else
			{
				// on ajoute a la fin
				
			}

		// export test+=vin si test existe pas ca doit l'ajouter
		}
		i++;
	}
	
	return (EXIT_SUCCESS);
}


/*
checkvalid(char *str) : 
	This function is called in builtin_export. It contains a list of char that would
	make an export name invalid.
*/
// int	checkvalid(char *str)
// {
// 	const char	*end = ft_strrchr(str, '=');

// 	while (str && *str && str != end)
// 	{
// 		if (*str == '-' || *str == '.' || *str == '{' || *str == '}'
// 			|| *str == '*' || *str == '#' || *str == '@' || *str == '!'
// 			|| *str == '^' || *str == '~' || *str == '\"' || *str == '|'
// 			|| *str == '\'' || *str == '$' || *str == ';' || *str == '&'
// 			|| !ft_isascii(*str) || ft_isspace(*str))
// 			return (0);
// 		if (*str == '+' && *(str + 1) != '=')
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// static int	len_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	if (!env)
// 		return (0);
// 	while (env[i])
// 		i++;
// 	return (i);
// }

// static void	copy_e(char **tmp, int ret, char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (data.envp[i])
// 	{
// 		tmp[i] = data.envp[i];
// 		i++;
// 	}
// 	/* IF IT DOES NOT EXIST */
// 	if  (ret == -1)
// 	{
// 		tmp[i] = ft_strdup(str);
// 		tmp[i + 1] = NULL;
// 	}
// 	/* ELSE */
// 	else
// 		tmp[ret] = str;
// }

// int	export(t_lst *commands)
// {
// 	int		i;
// 	int		flag;
// 	char	*env;

// 	i = 0;
// 	flag = 0;
// 	if (!commands->cmd[1])
// 		print_env();
// 	else if (check_format(commands->cmd[1]) != -1)
// 	{
// 		env = strdup(commands->cmd[1]);
// 		if (!env)
// 			return (EXIT_FAILURE);
// 		// faut verifier que la variable existe pas deja, auquel cas faut la remplacer
// 		while (data.envp[i] != NULL)
// 		{
// 			if (!ft_strncmp(data.envp[i], env, check_format(env)))
// 			{
// 				data.envp[i] = env;
// 				printf("test: %s\n", data.envp[i]);
// 				flag = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 		if (flag != 1)
// 		{
// 			data.envp[i] = env;
// 			printf("env: %s\n", env);
// 			// how? Do I need to reallocate memory to fit the new addition?
// 			data.envp[i + 1] = NULL;
// 		}
// 		free(env);
// 	}
// 	else
// 	{
// 		if (!ft_strncmp(commands->cmd[1], "-", 1))
// 		{
// 			error_usage_export(commands->cmd[1]);
// 			return (EXIT_FAILURE);
// 		}
// 		else if (commands->cmd[2] && !check_format(commands->cmd[2]))
// 			error_args(commands->cmd[2]);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }