#include "../../minishell.h"

void	error_cmd(char *bash, char *cmd_name, char *input)
{
	if (bash)
		ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(input, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void	error_usage(char *cmd_name, char *str, char *usage)
{
	char	*option;

	option = ft_substr(str, 0, 2);
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd(usage, STDERR_FILENO);
	free((void *)option);
}
