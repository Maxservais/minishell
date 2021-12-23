#include "../../minishell.h"

int	find_equal_c(char *str)
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

int	ft_find_plus(char *str)
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

int	len_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}
