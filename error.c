/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mservais <mservais@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:58:04 by mservais          #+#    #+#             */
/*   Updated: 2021/10/05 11:34:21 by mservais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_err_return(char *error)
{
	write(1, error, ft_strlen(error));
	return (1);
}

int	ft_perror(void)
{
	perror("Error");
	return (1);
}

int	report_error(void)
{
	perror("Error");
	return (-1);
}

int	ft_free(char ***argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != NULL)
		{
			free(argv[i][j]);
			j++;
		}
		free(argv[i]);
		i++;
	}
	free(argv);
	return (EXIT_FAILURE);
}
