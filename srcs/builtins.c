/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:46:38 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/11 12:51:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	i++;
	if (str[i])
		return (1);
	return (0);
}

void	error_option(char **args, char *cmd, int *status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": -", STDERR_FILENO);
	ft_putchar_fd(args[1][1], STDERR_FILENO);
	ft_putstr_fd(": invalid option", STDERR_FILENO);
	*status = 2;
}
