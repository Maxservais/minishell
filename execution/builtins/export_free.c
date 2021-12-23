#include "../../minishell.h"

void	free_exported(t_exported vars, char *str)
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

void	join_free(t_add_to_envp var, char *str)
{
	var.key = ft_substr(str, 0, var.plus);
	var.value = ft_substr(str, var.plus + 2, ft_strlen(str) - var.plus);
	var.tmp = ft_strjoin(var.key, "=");
	free(var.key);
	var.new_envp[var.i] = ft_strjoin(var.tmp, var.value);
	free(var.value);
	free(var.tmp);
}

int	free_new_envp(t_add_to_envp var)
{
	while (var.i-- > 0)
		free(var.new_envp[var.i]);
	free(var.new_envp);
	return (-1);
}
