/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:01:03 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/09 16:33:45 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_alloc(char *str, t_history *elem)
{
	free_null((void **)&(elem->cmd));
	elem->cmd = ft_strdup(str);
	if (!elem->cmd)
		exit_strerror();
}

void	write_ws(size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_write(0, " ", 1);
		i++;
	}
}

void	wipe_and_replace(t_read *data, t_history *elem)
{
	size_t	wipe_len;
	size_t	replace_len;

	wipe_len = ft_strlen(data->str);
	cursor_left(data->pos);
	write_ws(wipe_len);
	cursor_left(wipe_len);
	free_null((void **)&data->str);
	replace_len = ft_strlen(elem->cmd);
	if (elem->cmd)
		ft_write(0, elem->cmd, ft_strlen(elem->cmd));
	data->str = ft_strdup(elem->cmd);
	data->pos = replace_len;
	data->len = replace_len;
}
