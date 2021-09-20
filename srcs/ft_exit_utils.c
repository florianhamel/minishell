/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 11:12:34 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 02:59:45 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) > 3)
		return (0);
	if (!ft_isdigit(arg[i]))
		return (0);
	if (ft_atoi(arg) > 256)
		return (0);
	return (1);
}

int	check_nb_args(char **args)
{
	if (args[1] && is_numeric(args[1]) && args[2])
		return (0);
	return (1);
}

void	error_numeric(char *arg, int *status)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": valid numeric argument required\n", STDERR_FILENO);
	*status = 2;
}

void	error_nb_args(int *status)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", \
	STDERR_FILENO);
	*status = 1;
}
