/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:09:34 by mservais          #+#    #+#             */
/*   Updated: 2021/06/01 18:36:40 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	my_c;
	unsigned char	*ptr;

	i = 0;
	my_c = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		*(ptr + i) = my_c;
		i++;
	}
	return (s);
}
