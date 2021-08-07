/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:15:53 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/06 18:44:18 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read	*init_data(t_history **history)
{
	t_read		*data;
	t_history	*elem;

	elem = new_elem_history(NULL);
	push_front(elem, history);
	if (!(data = malloc(sizeof(t_read))))
		ft_exit();
	data->c = 0;
	data->pos = 0;
	data->len = 0; 
	data->current = elem;
	data->str = NULL;
	return (data);
}

int		ft_getc(t_read *data)
{
	int	c;

	c = 0;
	if (read(0, &c, sizeof(c)) < 0)
		exit_parsing(data);
	return (c);
}

int		get_last_char(t_read *data)
{
	int	c;
	struct termios	oterm;
	struct termios	term;

	tcgetattr(0, &oterm);
	ft_memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	c = ft_getc(data);
	tcsetattr(0, TCSANOW, &oterm);
	return (c);
}