/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 16:03:02 by mservais          #+#    #+#             */
/*   Updated: 2021/06/02 15:59:26 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		len;

	len = ft_strlen(s);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s, len + 1);
	return (dst);
}
