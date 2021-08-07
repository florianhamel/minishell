/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:07 by user42            #+#    #+#             */
/*   Updated: 2021/08/06 19:02:37 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	eof_mgmt(t_read *data)
{
	if (!data->str || data->str[0] == '\0')
	{
		free_parsing(data);
		printf("exit\n");
		exit(1);
	}
}

void	key_mgmt(t_read *data)
{
	if (data->c == CTRL_D)
		eof_mgmt(data);
	else if (data->c == RIGHT_KEY || data->c == LEFT_KEY)
		cursor_move(data);
	else if (data->c == UP_KEY || data->c == DOWN_KEY)
		history_navigation(data);
	else
		str_mgmt(data);
}

void	add_cmd(t_read *data, t_history **history)
{
	int	fd;

	fd = open("documents/.minishell_history", \
	O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == ERROR)
		ft_exit();
	ft_write(fd, "\n", 1);
	ft_write(fd, data->str, ft_strlen(data->str));
	replace_alloc(data->str, *history);
}

char	*get_cmd(t_history **history, int *status)
{
	t_read		*data;

	data = init_data(history);
	if (!data)
	{
		free_history(*history);
		ft_exit();
	}
	while (1)
	{
		data->c = get_last_char(data);
		if (data->c == NL_KEY || data->c == CTRL_C)
		{
			if (data->c == CTRL_C)
				*status = 1;
			else if (data->c == NL_KEY)
				add_cmd(data, history); // ISSUE THERE WHEN ONLY NL
			break;
		}
		else
			key_mgmt(data);
	}
	printf("\nprintf : %s\n", data->str);
	return (data->str);
}