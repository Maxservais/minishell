#include "../../minishell.h"

int	exported(char *str)
{
	t_exported	vars;

	vars.i = 0;
	vars.plus = ft_find_plus(str);
	vars.equal = find_equal_c(str);
	if (vars.plus != -1)
		vars.equal = vars.plus;
	vars.key_str = ft_substr(str, 0, vars.equal);
	while (g_data.envp[vars.i])
	{
		vars.tmp = ft_strdup(g_data.envp[vars.i]);
		vars.key_envp = ft_substr(g_data.envp[vars.i],
				0, find_equal_c(g_data.envp[vars.i]));
		if (!ft_strcmp_parse(vars.key_str,
				vars.key_envp, ft_strlen(vars.key_str)))
		{
			free_exported(vars, str);
			return (vars.i);
		}
		free(vars.tmp);
		free(vars.key_envp);
		vars.i++;
	}
	free(vars.key_str);
	return (-1);
}

int	add_to_envp(char *str)
{
	t_add_to_envp	var;

	var.i = 0;
	var.new_envp = malloc(sizeof(char *) * (len_env(g_data.envp) + 2));
	if (!var.new_envp)
		return (-1);
	while (g_data.envp[var.i] != NULL)
	{
		var.new_envp[var.i] = ft_strdup(g_data.envp[var.i]);
		if (!var.new_envp[var.i])
			return (free_new_envp(var));
		var.i++;
	}
	var.plus = ft_find_plus(str);
	if (var.plus != -1)
		join_free(var, str);
	else
		var.new_envp[var.i] = ft_strdup(str);
	var.i++;
	var.new_envp[var.i] = NULL;
	free_envp();
	g_data.envp = var.new_envp;
	return (EXIT_SUCCESS);
}

void	exported_ok(t_lst *commands, int i)
{
	if (exported(commands->cmd[i]) >= 0)
		g_data.exit_code = 0;
	else if (add_to_envp(commands->cmd[i]) == 0)
		g_data.exit_code = 0;
}
