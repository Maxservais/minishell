#include "../../minishell.h"

static void	error_args(char *str)
{
	ft_putstr_fd("bash: export: '", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int	check_export_name(char *s)
{
	int	i;
	int	plus;
	int	equal;

	plus = find_plus(s);
	equal = find_equal_c(s);
	if (equal == -1)
		equal = ft_strlen(s);
	if (plus != -1)
		equal = plus;
	i = 0;
	while (s[i] && i < equal)
	{
		if (s[i] == '.' || s[i] == '{' || s[i] == '-'  || s[i] == '}'
			|| s[i] == '$' || s[i] == '\'' || s[i] == ';' || s[i] == '&'
			|| s[i] == '\"'|| s[i] == '|' || s[i] == '^'  || s[i] == '~'
			|| s[i] == '*' || s[i] == '#' || s[i] == '@' || s[i] == '!'
			|| !ft_isascii(*s))
			{
				error_args(s);
				return (-1);
			}
		i++;
	}
	return (0);
}

static void	print_env(void)
{
	int		i;
	int		j;
	char	*var;
	char	*value;

	i = 0;
	while (g_data.envp[i] != NULL)
	{
		j = 0;
		while(g_data.envp[i][j])
		{
			if (g_data.envp[i][j] == '=')
			{
				var = ft_substr(g_data.envp[i], 0, j + 1);
				value = ft_substr(g_data.envp[i], j + 1, ft_strlen(g_data.envp[i]) - j);
				break ;
			}
			j++;
		}
		printf("declare -x %s\"%s\"\n", var, value);
		free(var);
		free(value);
		i++;
	}
}

char	*append_char(char *str, char *str_before)
{
	char	*key;
	char	*value;
	char	*to_append;
	char	*tmp1;
	char	*tmp2;
	char	*final;
	char	c;

	c = '=';
	key = ft_substr(str, 0, find_plus(str));
	value = ft_substr(str_before, find_equal_c(str_before) + 1, ft_strlen(str_before) - find_equal_c(str_before));
	to_append = ft_substr(str, find_equal_c(str) + 1, ft_strlen(str) - find_equal_c(str));
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

int	exported(char *str)
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

int	add_to_envp(char *str)
{
	int		i;
	int		plus;
	char	c;
	char	*key;
	char	*value;
	char	*tmp;
	char	**new_envp;

	i = 0;
	c = '=';
	new_envp = malloc(sizeof(char *) * (len_env(g_data.envp) + 2));
	if (!new_envp)
		return (-1);
	while (g_data.envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(g_data.envp[i]);
		if (!new_envp[i])
		{
			while (i-- > 0)
				free(new_envp[i]);
			free(new_envp);
			return (-1);
		}
		i++;
	}
	plus = find_plus(str);
	if (plus != -1)
	{
		key = ft_substr(str, 0, plus);
		value = ft_substr(str, plus + 2, ft_strlen(str) - plus);
		tmp = ft_strjoin(key, &c);
		free(key);
		new_envp[i] = ft_strjoin(tmp, value);
		free(value);
		free(tmp);
	}
	else
		new_envp[i] = ft_strdup(str);
	i++;
	new_envp[i] = NULL;
	free_envp();
	g_data.envp = new_envp;
	return (EXIT_SUCCESS);
}

int	export(t_lst *commands)
{
	int		i;

	if (!commands->cmd[1])
	{
		print_env();
		g_data.exit_code = 0;
		return (EXIT_SUCCESS);
	}
	i = 1;
	while (commands->cmd[i])
	{
		if (commands->cmd[i][0] == '=' || commands->cmd[i][0] == '+' || ft_isdigit(commands->cmd[i][0]))
		{
			error_args(commands->cmd[i]);
			g_data.exit_code = 1;
		}
		else if (check_export_name(commands->cmd[i]) == -1)
			g_data.exit_code = 1;
		else if (find_equal_c(commands->cmd[i]) != -1)
		{
			if (exported(commands->cmd[i]) >= 0)
				g_data.exit_code = 0;
			else if (add_to_envp(commands->cmd[i]) == 0)
				g_data.exit_code = 0;
		}
		i++;
	}
	return (g_data.exit_code);
}
