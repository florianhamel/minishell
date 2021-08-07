/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:14:47 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/06 11:10:49 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	cursor_left(int iter)
{
	int	i;

	i = 0;
	while (i < iter)
	{
		ft_write(0, "\033[1D", 4);
		i++;
	}
}

void	cursor_right(int iter)
{
	int	i;

	i = 0;
	while (i < iter)
	{
		ft_write(0, "\033[1C", 4);
		i++;
	}
}

void	cursor_move(t_read *data)
{
	if (data->c == RIGHT_KEY)
	{
		if (data->pos < data->len)
		{
			cursor_right(1);
			(data->pos)++;
		}
	}
	else if (data->c == LEFT_KEY)
	{
		if (data->pos > 0)
		{
			cursor_left(1);
			(data->pos)--;
		}
	}
}
