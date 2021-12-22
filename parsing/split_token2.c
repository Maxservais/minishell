#include "../minishell.h"

void	count_w_token(t_count_token arg)
{
	if (check_occ_tok(*arg.str, arg.o) && *(*arg.str) != arg.first_quote)
	{
		if (**arg.str == ' ')
			(*arg.counter)--;
		(*arg.counter)++;
		*arg.str += check_occ_tok(*arg.str, arg.o);
	}
	else if (!check_occ_tok(*arg.str, arg.o) && *(*arg.str) != arg.first_quote)
	{
		while (*(*arg.str) && !check_occ_tok(*arg.str, arg.o))
			(*arg.str)++;
		(*arg.counter)++;
	}
}

int	count_words_tok(char *str, t_operation *o)
{
	int		counter;
	int		x;
	char	first_quote;

	x = 0;
	counter = 0;
	first_quote = find_first_quote_tok(str);
	while (*str)
	{
		if (*str == first_quote)
		{
			str++;
			while (*str != first_quote)
				str++;
			str++;
			counter++;
		}
		first_quote = find_first_quote_tok(str);
		count_w_token((t_count_token){&counter, &str, o, first_quote});
	}
	return (counter);
}

static char	**factory(char **result, t_operation *o, char *str)
{
	int			words;

	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	words = count_words_tok(str, o);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	fill(result, str, o, words);
	free(str);
	return (result);
}

void	assignation_o(t_operation *o)
{
	o[0].operation = ">>";
	o[1].operation = "<<";
	o[2].operation = "<";
	o[3].operation = ">";
	o[4].operation = "$?";
	o[5].operation = "\'";
	o[6].operation = "\"";
	o[7].operation = "$";
	o[8].operation = " ";
	o[9].operation = "\n";
	o[10].operation = "\v";
	o[11].operation = "\t";
	o[12].operation = "\r";
	o[13].operation = "\f";
	o[14].operation = NULL;
}

char	**split_token(char *str)
{
	char			**result;
	t_operation		o[15];
	int				i;

	i = 0;
	while (i < 15)
	{
		if (i == 0 || i == 1 || i == 4)
			o[i].size = 2;
		else
			o[i].size = 1;
		i++;
	}
	assignation_o(o);
	result = NULL;
	return (factory(result, o, str));
}
