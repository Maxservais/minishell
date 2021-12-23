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

	plus = ft_find_plus(s);
	equal = find_equal_c(s);
	if (equal == -1)
		equal = ft_strlen(s);
	if (plus != -1)
		equal = plus;
	i = 0;
	while (s[i] && i < equal)
	{
		if (s[i] == '.' || s[i] == '{' || s[i] == '-' || s[i] == '}'
			|| s[i] == '$' || s[i] == '\'' || s[i] == ';' || s[i] == '&'
			|| s[i] == '\"' || s[i] == '|' || s[i] == '^' || s[i] == '~'
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
		while (g_data.envp[i][j])
		{
			if (g_data.envp[i][j] == '=')
			{
				var = ft_substr(g_data.envp[i], 0, j + 1);
				value = ft_substr(g_data.envp[i], j + 1,
						ft_strlen(g_data.envp[i]) - j);
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
	t_append_char	vars;

	vars.c = '=';
	vars.key = ft_substr(str, 0, ft_find_plus(str));
	vars.value = ft_substr(str_before, find_equal_c(str_before)
			+ 1, ft_strlen(str_before) - find_equal_c(str_before));
	vars.to_append = ft_substr(str, find_equal_c(str) + 1, ft_strlen(str)
			- find_equal_c(str));
	vars.tmp1 = ft_strjoin(vars.value, vars.to_append);
	vars.tmp2 = ft_strjoin(vars.key, &vars.c);
	vars.final = ft_strjoin(vars.tmp2, vars.tmp1);
	free(vars.key);
	free(vars.value);
	free(vars.to_append);
	free(vars.tmp1);
	free(vars.tmp2);
	return (vars.final);
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
		if (commands->cmd[i][0] == '=' || commands->cmd[i][0] == '+'
			|| ft_isdigit(commands->cmd[i][0]))
		{
			error_args(commands->cmd[i]);
			g_data.exit_code = 1;
		}
		else if (check_export_name(commands->cmd[i]) == -1)
			g_data.exit_code = 1;
		else if (find_equal_c(commands->cmd[i]) != -1)
			exported_ok(commands, i);
		i++;
	}
	return (g_data.exit_code);
}
