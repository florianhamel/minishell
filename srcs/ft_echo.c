/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 19:31:49 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 02:59:29 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 3))
		;
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	ft_free_arr(args);
	return (0);
}
