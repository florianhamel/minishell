/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:43:30 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/07 12:26:18 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*new_del(t_read *data)
{
	char	*new;
	char	*prev;
	char	*next;

	next = get_next(data);
	if (!next)
		exit_parsing(data);
	prev = new_alloc(data->str, data->pos - 1, data->pos - 1);
	if (!prev)
		exit_parsing(data);
	new = ft_strjoin(prev, next);
	cursor_left(1);
	ws_fd(ft_strlen(next) + 1, 0);
	cursor_left(ft_strlen(next) + 1);
	ft_write(0, next, ft_strlen(next));
	cursor_left(ft_strlen(next));
	ft_free(prev);
	ft_free(next);
	return (new);
}

char	*new_insert(t_read *data)
{
	char	*prev;
	char	*to_write;
	char	*new;
	
	to_write = get_to_write(data);
	prev = new_alloc(data->str, data->pos, data->pos);
	if (!prev)
		exit_parsing(data);
	new = ft_strjoin(prev, to_write);
	ft_write(0, to_write, ft_strlen(to_write));
	cursor_left(ft_strlen(to_write) - 1);
	ft_free(prev);
	ft_free(to_write);
	return (new);
}

char	*new_char(t_read *data)
{
	char	*new;

	new = new_alloc(data->str, data->pos + 1, data->pos);
	if (!new)
		exit_parsing(data);
	new[data->pos] = (char)data->c;
	ft_write(0, &data->c, sizeof(data->c));
	return (new);
}

void	str_mgmt(t_read *data)
{
	if (data->c == DEL_KEY)
	{
		if (data->pos > 0)
		{
			data->str = new_del(data);
			(data->pos)--;
			(data->len)--;
		}
	}
	else
	{
		if (data->pos < data->len)
			data->str = new_insert(data);
		else
			data->str = new_char(data);
		(data->pos)++;
		(data->len)++;
	}
}
