/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:16:53 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/09 18:38:47 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_data *data, char **args, int count)
{
	if (count == 0)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_free_arr(args);
	free_history(data->history);
	free_data(data);
}

int	ft_exit(t_data *data, char **args)
{
	int	count;
	int	status;
	int	i;

	status = 0;
	i = 0;
	count = 0;
	while (args[1] && args[1][i])
	{
		if (ft_isdigit(args[1][i]))
			i++;
		else
		{
			count = 1;
			printf("exit\nminishell: exit: numeric argument is required !\n");
			break ;
		}
	}
	if (data->cmd_lst->next)
	{
		ft_free_arr(args);
		return (status);
	}
	ft_free_exit(data, args, count);
	exit(status);
}
