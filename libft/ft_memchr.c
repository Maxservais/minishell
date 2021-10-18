/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 09:54:22 by mservais          #+#    #+#             */
/*   Updated: 2021/06/01 18:36:17 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s;
	unsigned char	my_c;

	i = 0;
	ptr_s = (unsigned char *)s;
	my_c = (unsigned char)c;
	while (i < n)
	{
		if (*(ptr_s + i) == my_c)
		{
			return (ptr_s + i);
		}
		i++;
	}
	return (NULL);
}
