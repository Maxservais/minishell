#include "minishell.h"

int	is_error(char *line)
{
	int	simple_quote;
	int	double_quote;

	simple_quote = 0;
	double_quote = 0;
	while (*line)
	{
		if (*line == '\'')
			simple_quote++;
		if (*line == '\"')
			double_quote++;
		line++;
	}
	if (simple_quote % 2 == 1 || double_quote % 2 == 1)
	{
		ft_putstr_fd("input error\n", 1);
		return (1);
	}
	return (0);
}

int	nbr_of_dollars(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
			count++;
		i++;
	}
	return (count);
}

void	rem_handcom_clean(t_lst *commands, t_token *tokens, char **splited)
{
	remove_files(commands);
	handle_command(commands);
	clean_all(tokens, splited, &commands);
}
