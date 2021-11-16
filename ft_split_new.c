/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xauffray <xauffray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:38:59 by xauffray          #+#    #+#             */
/*   Updated: 2021/11/16 16:12:28 by xauffray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_words(char const *s, char *sep)
{
	int	counter;
	int	x;
	int	length_word;

	counter = 0;
	x = 0;
	length_word = 0;
	while (*(char *)(s + x))
	{
		if (*(char *)(s + x) == sep)
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

static	char	*create_word(char const *ss, char *sep)
{
	char	*word;
	size_t	nextsep;
	int		x;
	int		y;

	y = 0;
	nextsep = 0;
	while (*(ss + y) && *(ss + y++) != sep)
		nextsep++;
	word = (char *)malloc(nextsep + 1);
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

static	char	**insert_words(char **tab, char const *s, char c)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (*(s + x))
	{
		if (*(s + x++) == c || !*(s + x))
		{
			tab[y] = create_word(s, c);
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

char	**ft_split(char const *s, char *sep)
{
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * count_words(s, sep));
	if (!tab)
		return (NULL);
	tab = insert_words(tab, s, sep);
	if (!tab)
		return (NULL);
	return (tab);
}
