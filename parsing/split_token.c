#include "../minishell.h"

static int	check_occ(char *str, t_operation *o)
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

static char	find_first_quote(char *str)
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

static int	count_words(char *str, t_operation *o)
{
	int		counter;
	int		x;
	char	first_quote;

	x = 0;
	counter = 0;
	first_quote = find_first_quote(str);
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
		first_quote = find_first_quote(str);
		if (check_occ(str, o) && *(str) != first_quote)
		{
			if (*str == ' ')
				counter--;
			counter++;
			str += check_occ(str, o);
		}
		else if (!check_occ(str, o) && *(str) != first_quote)
		{
			while (*(str) && !check_occ(str, o))
				str++;
			counter++;
		}
	}
	return (counter);
}

static	char	*create_word(char *str, t_operation *o, int *i)
{
	char	*word;
	int		len;
	char	first_quote;

	first_quote = find_first_quote(str);
	len = 0;
	if (check_occ(str, o) && *str != first_quote)
	{
		len = check_occ(str, o);
		word = malloc(sizeof(char) * (len + 1));
		if (!word)
			return (NULL);
		while (len)
		{
			word[*i] = (str)[*i];
			(*i)++;
			len--;
		}
		word[*i] = '\0';
		return (word);
	}
	while (*(str + *i) && !check_occ(str + (*i)++, o))
		len++;
	*i = 0;
	if (*(str + *i) == first_quote)
	{
		(*i)++;
		while (*(str + *i) != first_quote)
		{
			(*i)++;
			len++;
		}
		(*i)++;
	}
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	*i = 0;
	while (len--)
	{
		if (*str == first_quote)
			word[*i] = (str)[(*i) + 1];
		else
			word[*i] = (str)[(*i)];
		(*i)++;
	}
	word[*i] = '\0';
	if (*str == first_quote)
		(*i) += 2;
	return (word);
}

static void fill(char **result, char *str, t_operation *o, int size)
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
}

static char	**factory(char **result, t_operation *o, char *str)
{
	int			words;

	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	words = count_words(str, o);
	result = malloc(sizeof(char *) * (words + 1));
	if  (!result)
	{
		free(str);
		return (NULL);
	}
	fill(result, str, o, words);
	free(str);
	return (result);
}

char	**split_token(char *str)
{
	char			**result;
	t_operation		o[15] =
	{
		{">>", 2},
		{"<<", 2},
		{"<", 1},
		{">", 1},
		{"$?", 2},
		{"\'", 1},
		{"\"", 1},
		{"$", 1},
		{" ", 1},
		{"\n", 1},
		{"\v", 1},
		{"\t", 1},
		{"\r", 1},
		{"\f", 1},
		{NULL, 1}
	};

	result = NULL;
	return (factory(result, o, str));
}
