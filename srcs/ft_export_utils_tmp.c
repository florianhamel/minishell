/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_tmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:45:49 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/11 16:51:14 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	only_export(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		ft_putstr_fd("export ", STDOUT_FILENO);
		ft_putstr_fd(data->env[i], STDOUT_FILENO);
	}
}

void	error_identifier(char *arg, int *status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier", STDERR_FILENO);
	*status = 1;
}
