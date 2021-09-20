/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 16:09:57 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 02:59:35 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	int		status;
	char	**env;
	int		i;

	status = 0;
	env = get_env(data);
	i = 0;
	if (args[1] && is_option(args[1]))
		error_option(args[1], "env", &status);
	else if (args[1])
		error_arg(args[1], "env", &status);
	else
	{
		while (env[i])
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
			i++;
		}
	}
	ft_free_arr(args);
	ft_free_arr(env);
	return (status);
}
