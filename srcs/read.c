/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:07 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 21:21:00 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eof_mgmt(t_read *data)
{
	if (!data->str || data->str[0] == '\0')
	{
		free_parsing(data);
		printf("exit\n");
		exit(0);
	}
}

int		is_valid_input(int c)
{
	if (32 <= c && c <= 127)
		return (1);
	return (0);
}

void	key_mgmt(t_read *data)
{
	if (data->c == CTRL_D)
		eof_mgmt(data);
	else if (data->c == RIGHT_KEY || data->c == LEFT_KEY)
		cursor_move(data);
	else if (data->c == UP_KEY || data->c == DOWN_KEY)
		history_navigation(data);
	else if (32 <= data->c && data->c <= 127)
		str_mgmt(data);
}

void	add_cmd(t_read *data, t_history **history)
{
	int			fd;

	fd = open("documents/.minishell_history", \
	O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == ERROR)
		exit_strerror();
	if (data->str)
	{
		ft_write(fd, "\n", 1);
		ft_write(fd, data->str, ft_strlen(data->str));
		replace_alloc(data->str, *history);
		push_front(new_elem_history(NULL), history);
	}
}

t_read	*get_input(t_data *data)
{
	t_read		*data_parsing;

	data_parsing = init_read(data);
	if (!data_parsing)
	{
		free_history(data->history);
		exit_strerror();
	}
	while (1)
	{
		data_parsing->c = get_last_char(data_parsing);
		if (data_parsing->c == NL_KEY || data_parsing->c == CTRL_C)
		{
			if (data_parsing->c == CTRL_C)
				abort_cmd(data_parsing, &(data->status));
			else if (data_parsing->c == NL_KEY)
				add_cmd(data_parsing, &(data->history));
			break ;
		}
		else
			key_mgmt(data_parsing);
	}
	printf("\n");
	return (data_parsing);
}
