/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:18:20 by mservais          #+#    #+#             */
/*   Updated: 2021/08/30 14:38:24 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/printf.h"

int	ft_pad_space(int size, int limit)
{
	int	i;

	i = 0;
	while (size < limit)
	{
		ft_putchar(' ');
		size++;
		i++;
	}
	return (i);
}
