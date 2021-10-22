#include "minishell.h"

// void	error_cmd(char *cmd_name, char *str)
// {
// 	ft_putstr_fd(cmd_name, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 	if (str)
// 	{
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		ft_putendl_fd(str, STDERR_FILENO);
// 	}
// }

// void	error_usage(char *option, char *cmd_name, char *error_msg)
// {
// 	char	*opt;

// 	opt = ft_substr(option, 0, 2);
// 	ft_putstr_fd("bash: export: ", STDERR_FILENO);
// 	ft_putstr_fd(cmd_name, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(opt, STDERR_FILENO);
// 	ft_putendl_fd(": invalid option", STDERR_FILENO);
// 	ft_putendl_fd(error_msg, STDERR_FILENO);
// 	free((void *)opt);
// }