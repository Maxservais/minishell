#include "../minishell.h"

int	ft_err_return(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

int	ft_perror(void)
{
	perror("error");
	return (1);
}

int	report_error(void)
{
	perror("error");
	return (-1);
}

int	ft_free(char ***argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != NULL)
		{
			free(argv[i][j]);
			j++;
		}
		free(argv[i]);
		i++;
	}
	free(argv);
	return (EXIT_FAILURE);
}