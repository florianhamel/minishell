/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 12:43:30 by fhamel            #+#    #+#             */
/*   Updated: 2021/05/09 18:00:37 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*new_del(char *str, size_t pos)
{
	char	*new;
	char	*prev;
	char	*next;

	if (!(next = get_next(str, pos)))
		return (NULL);
	if (!(prev = new_alloc(str, pos - 1, pos - 1)))
		return (NULL);
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

char	*new_insert(char *str, size_t pos, int c)
{
	char	*prev;
	char	*to_write;
	char	*new;
	
	if (!(to_write = get_to_write(str, pos, c)))
		return (NULL);
	if (!(prev = new_alloc(str, pos, pos)))
		return (NULL);
	new = ft_strjoin(prev, to_write);
	ft_write(0, to_write, ft_strlen(to_write));
	cursor_left(ft_strlen(to_write) - 1);
	ft_free(prev);
	ft_free(to_write);
	return (new);
}

char	*new_char(char *str, size_t len, int c)
{
	char	*new;

	if (!(new = new_alloc(str, len + 1, len)))
		return (NULL);
	new[len] = (char)c;
	ft_write(0, &c, sizeof(c));
	return (new);
}

void	str_mgmt(t_read *data)
{
	if (data->c == DEL_KEY)
	{
		if (data->pos > 0)
		{
			data->str = new_del(data->str, data->pos);
			(data->pos)--;
			(data->len)--;
		}
	}
	else
	{
		if (data->pos < data->len)
			data->str = new_insert(data->str, data->pos, data->c);
		else
			data->str = new_char(data->str, data->len, data->c);
		(data->pos)++;
		(data->len)++;
	}
}
