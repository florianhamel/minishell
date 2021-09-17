/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:16:53 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/16 13:25:41 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_data *data, char **args, int status)
{
	ft_free_arr(args);
	free_history(data->history);
	free_data(data);
	exit(status);
}

void	exit_no_pipe(t_data *data, char **args, int *status)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!check_nb_args(args))
	{
		error_nb_args(status);
		return ;
	}
	if (args[1] && !is_numeric(args[1]))
		error_numeric(args[1], status);
	*status = ft_atoi(args[1]);
	free_exit(data, args, *status);
}

void	exit_pipe(char **args, int *status)
{
	if (!check_nb_args(args))
	{
		error_nb_args(status);
		return ;
	}
	if (args[1] && !is_numeric(args[1]))
	{
		error_numeric(args[1], status);
		return ;
	}
	*status = ft_atoi(args[1]);
}

int	ft_exit(t_data *data, char **args)
{
	int	status;

	status = data->status;
	if (!data->cmd_lst->next)
		exit_no_pipe(data, args, &status);
	else
		exit_pipe(args, &status);
	ft_free_arr(args);
	return (status);
}
