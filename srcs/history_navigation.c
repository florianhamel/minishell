/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_navigation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:51:47 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/19 22:29:10 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_up(t_read *data)
{
	if (data->current->next)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->next);
		data->current = data->current->next;
	}
	else
	{
		cursor_right(1);
		cursor_left(1);
	}
	return ;
}

void	go_down(t_read *data)
{
	if (data->current->prev)
	{
		if (data->str)
			replace_alloc(data->str, data->current);
		wipe_and_replace(data, data->current->prev);
		data->current = data->current->prev;
	}
	else
	{
		cursor_right(1);
		cursor_left(1);
	}
}

void	history_navigation(t_read *data)
{
	if (data->c == UP_KEY)
		go_up(data);
	else if (data->c == DOWN_KEY)
		go_down(data);
}
