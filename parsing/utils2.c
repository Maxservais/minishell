#include "../minishell.h"

int	last_infile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->infile[x + 1].name)
		x++;
	return (x);
}

int	last_outfile(t_lst *command)
{
	int	x;

	x = 0;
	while (command->outfile[x + 1].name)
		x++;
	return (x);
}

int	find_equal(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

int	find_f_quote(char *line, int dollar)
{
	int		x;

	x = 0;
	while (line[x])
	{
		if (line[x] == '\'' && x == dollar -1)
			return (x);
		x++;
	}
	return (-1);
}

int	find_sec_quote(char *line, int first_quote)
{
	while (line[first_quote])
	{
		if (line[first_quote] == '\'')
			return (first_quote);
		first_quote++;
	}
	return (-1);
}
