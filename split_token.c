#include "minishell.h"
#include <stdio.h>

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

static int	count_token(char *str, t_operation *o)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (str[x])
	{
		if (check_occ(str + x, o))
			counter++;
		x++;
	}
	return (counter);
}

static int	count_words(char *str, t_operation *o)
{
	int counter;
	int x;

	x = 0;
	counter = 0;
	while (*str)
	{
		if (check_occ(str + x, o))
		{
			if (*str == ' ')
				counter--;
			counter++;
			str += check_occ(str + x, o);
		}
		else
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

	len = 0;
	if (check_occ(str, o))
	{
		len = check_occ(str, o);
		word = malloc(sizeof(char) * (len + 1));
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
	word = malloc(sizeof(char) * (len + 1));
	*i = 0;
	while (len--)
	{
		word[*i] = (str)[(*i)];
		(*i)++;
	}
	word[*i] = '\0';
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

char	**split_token(char *str, t_operation *o)
{
	char	**result;
	int		words;

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

int	main(void)
{
	char				**result;
	int					x = 0;
	t_operation			o[14] =
	{
		{">>", 2},
		{"<<", 2},
		{"<", 1},
		{">", 1},
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
	result = split_token("  < infile<main.c   cat  >outfile $xav >> test <<yo", o);
	// result = split_token("test >> oui << non", o);
	while (result[x])
	{
	    printf("%s\n", result[x]);
	    free(result[x++]);
	}
	free(result);
	// system("leaks a.out");
	return (0);
}
