/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 11:28:48 by mservais          #+#    #+#             */
/*   Updated: 2021/10/26 14:31:58 by xauffray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*str;
	unsigned char	my_c;

	i = 0;
	str = (char *)s;
	my_c = (unsigned char)c;
	while (*(str + i) != my_c)
	{
		if (*(str + i) == '\0')
		{
			return (NULL);
		}
		i++;
	}
	return (str + i);
}
