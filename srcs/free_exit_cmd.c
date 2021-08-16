/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:20:59 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/16 15:37:27 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	ft_free_arr(data->env);
	free_cmd_lst(data->cmd_lst);
	free_null((void **)&(data->str));
	free_null((void **)&data);
}

void	exit_custom(t_data *data, char *serror, int flag)
{
	free_history(data->history);
	free_data(data);
	if (flag == CUSTOM)
	{
		printf("%s\n", serror);
		exit(data->status);
	}
	exit_strerror();
}