/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 12:07:46 by mservais          #+#    #+#             */
/*   Updated: 2021/06/01 18:37:52 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				length;
	char			*str;
	unsigned char	my_c;

	str = (char *)s;
	my_c = (unsigned char)c;
	length = ft_strlen(str);
	if (my_c == '\0' && *(str + length) == '\0')
	{
		return (str + length);
	}
	while (length > 0)
	{
		if (*(str + length - 1) == my_c)
		{
			return (str + length - 1);
		}
		length--;
	}
	return (NULL);
}
