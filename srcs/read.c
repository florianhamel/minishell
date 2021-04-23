/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:07 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 13:00:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*key_mgmt(t_read *data)
{
	if (data->c == RIGHT_KEY || data->c == LEFT_KEY)
		cursor_mgmt(data);
	else if (data->c == UP_KEY || data->c == DOWN_KEY)
		data->str = history_mgmt();
	else
		data->str = str_mgmt(data);
	return (data->str);
}

char	*read_mgmt(void)
{
	t_read		*data;

	if (!(data = init_data()))
		return (NULL);
	while (1)
	{
		data->c = get_last_char();
		if (data->c == NL_KEY)
			break;
		else if (!(data->str = key_mgmt(data)))
			return (NULL);
	}
	printf("\n%s\n", data->str);
	return (data->str);
}