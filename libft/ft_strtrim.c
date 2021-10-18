/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 12:32:28 by mservais          #+#    #+#             */
/*   Updated: 2021/07/06 14:07:16 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_belongs(char const *set, char c)
{
	int		i;

	i = 0;
	while (*(set + i) != '\0')
	{
		if (*(set + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (*(s1 + i) != '\0' && ft_belongs(set, *(s1 + i)))
		i++;
	while ((j > i) && ft_belongs(set, *(s1 + j)))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
