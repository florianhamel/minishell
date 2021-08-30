/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:20:59 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/30 02:06:45 by fhamel           ###   ########.fr       */
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
		return ("Success");
	else if (status == 1)
		return ("No such file or directory");
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
		printf("minishell: ");
		if (word)
			printf("%s", word);
		printf("%s\n", custom_strerror(data->status));
		exit(status);
	}
	exit_strerror();
}