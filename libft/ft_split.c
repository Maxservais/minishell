/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:57:28 by mservais          #+#    #+#             */
/*   Updated: 2021/07/06 16:03:23 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordsinstring(char const *s, char c)
{
	int		w;

	w = 0;
	while (*s != '\0')
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
			w++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (w);
}

static int	ft_substrlen(char const *s, char c)
{
	int		i;

	i = 0;
	while (*(s + i) != '\0' && *(s + i) != c)
		i++;
	return (i);
}

static void	*ft_free(char **tab, int k)
{
	while (k > 0)
	{
		k--;
		free(tab[k]);
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		k;
	int		nbr;
	char	**tab;

	if (!s)
		return (NULL);
	nbr = ft_wordsinstring(s, c);
	tab = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!tab)
		return (NULL);
	k = 0;
	while (k < nbr)
	{
		while (*s != '\0' && *s == c)
			s++;
		tab[k] = ft_substr(s, 0, ft_substrlen(s, c));
		if (!tab)
			return (ft_free(tab, k));
		s = s + ft_substrlen(s, c);
		k++;
	}
	tab[k] = 0;
	return (tab);
}
