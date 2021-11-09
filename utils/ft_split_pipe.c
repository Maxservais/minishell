/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xauffray <xauffray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:57:28 by mservais          #+#    #+#             */
/*   Updated: 2021/11/09 11:23:09 by xauffray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	in_quotes(t_token *tokens, int pos)
{
	int	x;
	int	open_quote;
	int close_quote;

	x = 0;
	open_quote = 0;
	close_quote = 0;
	while (tokens[x].token)
	{
		if ((tokens[x].token == '\'' || tokens[x].token == '\"') && !open_quote)
			open_quote = tokens[x++].index;
		if ((tokens[x].token == '\'' || tokens[x].token == '\"') && !close_quote)
			close_quote = tokens[x].index;
		x++;
	}
	if (pos > open_quote && pos < close_quote)
		return (1);
	return (0);
}

static int	ft_wordsinstring(char const *s, t_token *tokens)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	y = 0;
	z = 0;
	while (s[z])
	{
		while (s[z] && s[z] == '|')
			z++;
		if (s[z] && s[z] != '|' && !in_quotes(tokens, z))
			x++;
		while (s[z] && s[z] != '|')
			z++;
	}
	return (x);
}

static int	ft_substrlen(char const *s, t_token *tokens)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (s[x])
	{
		if (s[x] == '|' && in_quotes(tokens, x))
			break ;
		x++;
	}
	return (x);
}

static void	*ft_freeee(char **tab, int k)
{
	while (k > 0)
	{
		k--;
		free(tab[k]);
	}
	free(tab);
	return (NULL);
}

char	**ft_split_pipe(char const *line, t_token *tokens)
{
	int		k;
	int		nbr;
	char	**tab;
	int		x;

	if (!line)
		return (NULL);
	nbr = ft_wordsinstring(line, tokens);
	tab = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!tab)
		return (NULL);
	k = 0;
	x = 0;
	while (k < nbr)
	{
		while (*line && *line == '|' && !in_quotes(tokens, x))
		{
			line++;
			x++;
		}
		tab[k] = ft_substr(line, 0, ft_substrlen(line, tokens));
		if (!tab)
			return (ft_freeee(tab, k));
		line += ft_substrlen(line, tokens);
		k++;
	}
	tab[k] = 0;
	return (tab);
}
