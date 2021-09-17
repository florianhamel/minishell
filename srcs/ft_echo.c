/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:31:49 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/14 13:23:05 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (ft_strncmp(args[1], "-n", 3) == 0)
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (ft_strncmp(args[1], "-n", 3) == 0)
		return (0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_free_arr(args);
	return (0);
}
