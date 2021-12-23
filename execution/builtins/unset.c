#include "../../minishell.h"

static void	var_loop(t_find_var_unset *vars)
{
	int	i;

	i = 0;
	while (g_data.envp[i])
	{
		vars->key_envp = ft_substr(g_data.envp[i],
				0, find_equal_c(g_data.envp[i]));
		if (!ft_strcmp_parse(vars->key_str,
				vars->key_envp, ft_strlen(vars->key_str)))
		{
			ft_bzero(g_data.envp[i], ft_strlen(g_data.envp[i]));
			free(g_data.envp[i]);
			free(vars->key_envp);
			while (g_data.envp[i])
			{
				g_data.envp[i] = g_data.envp[i + 1];
				i++;
			}
		}
		else
		{
			free(vars->key_envp);
			i++;
		}
	}
}

static int	find_var(char *str)
{
	t_find_var_unset	vars;

	vars.equal = find_equal_c(str);
	vars.key_str = ft_substr(str, 0, vars.equal);
	var_loop(&vars);
	free(vars.key_str);
	return (EXIT_SUCCESS);
}

int	unset(t_lst *commands)
{
	int	i;

	if (!g_data.envp)
		return (1);
	i = 1;
	while (commands->cmd[i])
	{
		if (find_var(commands->cmd[i]) == 1)
			g_data.exit_code = 1;
		i++;
	}
	return (EXIT_SUCCESS);
}
