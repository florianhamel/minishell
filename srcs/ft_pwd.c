/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:41:35 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 03:00:48 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args)
{
	int		status;
	char	cwd[PATH_MAX_B];

	status = 0;
	if (args[1] && is_option(args[1]))
		error_option(args[1], "pwd", &status);
	else if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr_fd(cwd, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: error retrieving current directory\n", \
		STDERR_FILENO);
		status = 1;
	}
	ft_free_arr(args);
	return (status);
}
