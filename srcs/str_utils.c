/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:30:54 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/08 11:48:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next(t_read *data)
{
	char	*next;
	int		pos;
	int		i;

	pos = data->pos;
	i = 0;
	next = malloc(ft_strlen(data->str) - pos + 1);
	if (!next)
		exit_parsing(data);
	while (data->str[pos])
	{
		next[i] = data->str[pos];
		pos++;
		i++;
	}
	next[i] = '\0';
	return (next);
}

char	*get_to_write(t_read *data)
{
	char	*to_write;
	int		pos;
	int		i;

	pos = data->pos;
	i = 1;
	to_write = malloc(ft_strlen(data->str) - data->pos + 2);
	if (!to_write)
		exit_parsing(data);
	to_write[0] = (char)data->c;
	while (data->str[pos])
	{
		to_write[i] = data->str[pos];
		pos++;
		i++;
	}
	to_write[i] = '\0';
	return (to_write);
}
