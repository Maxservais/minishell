#include "../../minishell.h"

void	free_unset(t_find_var_unset vars, char *str)
{
	free(g_data.envp[vars.i]);
	if (vars.plus != -1)
		g_data.envp[vars.i] = append_char(str, g_data.envp[vars.i]);
	else
		g_data.envp[vars.i] = ft_strdup(str);
	free(vars.tmp);
	free(vars.key_str);
	free(vars.key_envp);
}

void	check_find_var(t_find_var_unset vars, char *str)
{
	vars.tmp = ft_strdup(g_data.envp[vars.i]);
	vars.key_envp = ft_substr(g_data.envp[vars.i],
			0, find_equal_c(g_data.envp[vars.i]));
	if (!ft_strcmp_parse(vars.key_str,
			vars.key_envp, ft_strlen(vars.key_str)))
	{
		free_unset(vars, str);
		//printf("var = |%s|\n", g_data.envp[vars.i]);
		free(g_data.envp[vars.i]);
		ft_bzero(g_data.envp[vars.i], ft_strlen(g_data.envp[vars.i]));
		vars.ok = 1;
		while (g_data.envp[vars.i])
		{
			g_data.envp[vars.i] = g_data.envp[vars.i + 1];
			vars.i++;
		}
	}
	else
	{
		free(vars.tmp);
		free(vars.key_envp);
		vars.i++;
	}
}

int	find_var(char *str)
{
	t_find_var_unset	vars;

	vars.i = 0;
	vars.equal = find_equal_c(str);
	vars.key_str = ft_substr(str, 0, vars.equal);
	while (g_data.envp[vars.i])
		check_find_var(vars, str);
	if (vars.ok == 1)
		return (EXIT_SUCCESS);
	else
	{
		free(vars.key_str);
		return (EXIT_FAILURE);
	}
}

int	unset(t_lst *commands)
{
	if (!ft_strncmp(commands->cmd[1], "-", 1))
	{
		if (ft_strcmp(commands->cmd[1], "-f")
			&& ft_strcmp(commands->cmd[1], "-v"))
		{
			error_usage("unset: ", commands->cmd[1],
				"unset: usage: unset [-f] [-v] [name ...]");
			return (EXIT_FAILURE);
		}
		else if (find_var(commands->cmd[2]) == 1)
			return (EXIT_FAILURE);
	}
	else if (commands->cmd[1])
		if (find_var(commands->cmd[1]) == 1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
