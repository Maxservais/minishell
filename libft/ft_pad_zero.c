/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad_zero.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:19:57 by mservais          #+#    #+#             */
/*   Updated: 2021/08/30 13:15:36 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/printf.h"

int	ft_pad_zero(int size, int limit)
{
	int	i;

	i = 0;
	while (size < limit)
	{
		ft_putchar('0');
		size++;
		i++;
	}
	return (i);
}
