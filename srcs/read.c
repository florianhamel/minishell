/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:07 by user42            #+#    #+#             */
/*   Updated: 2021/06/04 17:24:42 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void		eof_mgmt(char *str)
{
	if (!str || str[0] == '\0')
	{
		printf("exit\n");
		exit(1);
	}
}

void		key_mgmt(t_read *data)
{
	if (data->c == CTRL_D)
		eof_mgmt(data->str);
	else if (data->c == RIGHT_KEY || data->c == LEFT_KEY)
		cursor_mgmt(data);
	else if (data->c == UP_KEY || data->c == DOWN_KEY)
		history_mgmt(data);
	else
		str_mgmt(data);
}

void	add_cmd(t_read *data, t_history **history)
{
	int			fd;

	if ((fd = open("documents/.minishell_history", O_WRONLY | O_APPEND)) < 0)
		ft_exit();
	ft_write(fd, "\n", 1);
	ft_write(fd, data->str, ft_strlen(data->str));
	replace_alloc(data->str, *history);
}

char	*get_cmd(t_history **history, int *status)
{
	t_read		*data;

	if (!(data = init_data(history)))
		ft_exit();
	while (1)
	{
		data->c = get_last_char();
		if (data->c == NL_KEY || data->c == CTRL_C)
		{
			if (data->c == CTRL_C)
				*status = 1;
			else if (data->c == NL_KEY)
				add_cmd(data, history);
			break;
		}
		else
			key_mgmt(data);
	}
	printf("\nprintf : %s\n", data->str);
	return (data->str);
}