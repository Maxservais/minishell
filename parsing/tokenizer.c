#include "../minishell.h"

static int	count_token(char *line)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (line[x])
	{
		if (check_occurence(line[x], "<>()\'\"|$"))
			counter++;
		x++;
	}
	return (counter);
}

t_token	*token_finder(char *line)
{
	t_token		*tokens;
	int			x;
	int			y;

	tokens = malloc(sizeof(t_token) * (count_token(line) + 1));
	if (!tokens)
		return (NULL);
	x = 0;
	y = 0;
	while (line[x])
	{
		if (check_occurence(line[x], "<>()\'\"|$"))
		{
			tokens[y].index = x;
			tokens[y].token = line[x];
			y++;
		}
		x++;
	}
	tokens[y].token = 0;
	return (tokens);
}
