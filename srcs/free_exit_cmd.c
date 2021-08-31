/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:20:59 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/31 02:19:55 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data)
{
	ft_free_arr(data->env);
	free_cmd_lst(data);
	free_null((void **)&(data->str));
	free_null((void **)&data);
}

char	*custom_strerror(int status)
{
	if (status == 0)
		return ("Success\n");
	else if (status == 1)
		return ("No such file or directory\n");
	else if (status == 127)
		return ("command not found\n");
	return (NULL);
}

void	exit_custom(t_data *data, char *word, int flag)
{
	int	status;

	status = data->status;
	free_history(data->history);
	free_data(data);
	if (flag == CUSTOM)
	{
		ft_putstr_fd("minishell: ", 2);
		if (word)
		{
			ft_putstr_fd(word, 2);
			ft_putstr_fd(": ", 2);
		}
		free_null((void **)&word);
		ft_putstr_fd(custom_strerror(status), 2);
		exit(status);
	}
	exit_strerror();
}
