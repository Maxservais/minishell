/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:52:38 by mservais          #+#    #+#             */
/*   Updated: 2021/06/02 18:38:50 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	while (i < n && *(s1 + i) != '\0' && *(s1 + i) == *(s2 + i))
		i++;
	if (i == n)
		res = 0;
	else
		res = (unsigned char)*(s1 + i) - (unsigned char)*(s2 + i);
	return (res);
}
