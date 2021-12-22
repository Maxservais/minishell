#include "../minishell.h"

static	int	count_words(char *s, t_token *tokens)
{
	int	counter;
	int	length_word;
	int	x;

	counter = 0;
	x = 0;
	length_word = 0;
	while (s[x])
	{
		if (s[x] == '|' && !in_quotes(tokens, x))
		{
			x++;
			length_word = 0;
		}
		else
		{
			if (!length_word)
				counter++;
			length_word++;
			x++;
		}
	}
	return (counter + 1);
}

static	char	*create_word(char *ss, t_token *tokens)
{
	char	*word;
	size_t	nextsep;
	int		x;
	int		y;

	y = 0;
	nextsep = 0;
	while ((ss[y] && ss[y] != '|')
		|| (ss[y] && ss[y] == '|' && in_quotes(tokens, y)))
	{
		y++;
		nextsep++;
	}
	word = malloc(nextsep + 1);
	if (!word)
		return (NULL);
	x = -1;
	while (nextsep-- && ss[++x])
		word[x] = ss[x];
	word[++x] = '\0';
	return (word);
}

static char	**check_free(char **tab, int y)
{
	if (!tab[y])
	{
		while (y > 0)
			free(tab[--y]);
		free(tab);
		return (NULL);
	}
	return (tab);
}

static	char	**insert_words(char **tab, char *s, t_token *tokens)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*(s + x))
	{
		if ((*(s + x++) == '|' && !in_quotes(tokens, x - 1)) || !*(s + x))
		{
			tab[y] = create_word(s, tokens);
			tab = check_free(tab, y);
			if (!tab)
				return (NULL);
			if (tab[y] && ft_strlen(tab[y]))
				y++;
			else if (!*tab[y])
				free(tab[y]);
			s += x;
			x = 0;
		}
	}
	tab[y] = NULL;
	return (tab);
}

char	**ft_test(char *s, t_token *tokens)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * count_words(s, tokens));
	if (!tab)
		return (NULL);
	tab = insert_words(tab, s, tokens);
	if (!tab)
		return (NULL);
	return (tab);
}
