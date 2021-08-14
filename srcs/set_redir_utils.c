/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:50:28 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/14 15:36:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_flag_in(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '<')
	{
		(*pos)++;
		return (DOUBLE_LEFT);
	}
	return (SIMPLE_LEFT);
}

int		get_flag_out(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '>')
	{
		(*pos)++;
		return (DOUBLE_RIGHT);
	}
	return (SIMPLE_RIGHT);
}

char	*get_word(t_data *data, int *pos)
{
	*pos += skip_ws(&data->str[*pos]);

}
