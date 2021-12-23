#include "../minishell.h"

int	check_occ_tok(char *str, t_operation *o)
{
	int	x;

	x = 0;
	while (o[x].operation)
	{
		if (!ft_strncmp(o[x].operation, str, o[x].size))
			return (o[x].size);
		x++;
	}
	return (0);
}

char	find_first_quote_tok(char *str)
{
	int		x;
	char	first_quote;

	x = 0;
	first_quote = 0;
	while (str[x])
	{
		if (str[x] == '\'' || str[x] == '\"')
			return (str[x]);
		x++;
	}
	return (0);
}

static	char	*create_word(char *str, t_operation *o, int *i)
{
	char	*word;
	int		len;
	char	first_quote;

	first_quote = find_first_quote_tok(str);
	len = 0;
	if (check_occ_tok(str, o) && *str != first_quote)
	{
		len = check_occ_tok(str, o);
		word = malloc(sizeof(char) * (len + 1));
		if (!word)
			return (NULL);
		while (len)
			ft_str_word(word, i, str, &len);
		word[*i] = '\0';
		return (word);
	}
	len = check_for_quote((t_check_quote){i, str, o, first_quote, len});
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	copy_word((t_copy_word){i, str, first_quote, word, len});
	return (word);
}

void	fill(char **result, char *str, t_operation *o, int size)
{
	int		x;
	int		i;

	x = 0;
	while (size)
	{
		i = 0;
		while (*str == ' ')
			str++;
		result[x++] = create_word(str, o, &i);
		str += i;
		size--;
	}
	result[x] = NULL;
	x = 0;
}
