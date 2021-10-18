/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 10:57:24 by mservais          #+#    #+#             */
/*   Updated: 2021/06/01 18:36:23 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	int				res;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	i = 0;
	res = 0;
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (i < n)
	{
		if (*(ptr_s1 + i) == *(ptr_s2 + i))
		{
			i++;
		}
		else
		{
			return (res = *(ptr_s1 + i) - *(ptr_s2 + i));
		}
	}
	return (0);
}
