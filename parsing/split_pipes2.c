#include "../minishell.h"

int	in_quotes(t_token *tokens, int pos)
{
	int	x;
	int	open_quote;
	int	close_quote;

	x = 0;
	open_quote = -1;
	close_quote = -1;
	while (tokens[x].token)
	{
		if ((tokens[x].token == '\''
				|| tokens[x].token == '\"') && open_quote == -1)
			open_quote = tokens[x].index;
		else if ((tokens[x].token == '\''
				|| tokens[x].token == '\"') && close_quote == -1)
			close_quote = tokens[x].index;
		x++;
	}
	if (pos > open_quote && pos < close_quote)
		return (1);
	return (0);
}
