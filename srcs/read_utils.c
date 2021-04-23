/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:15:53 by fhamel            #+#    #+#             */
/*   Updated: 2021/04/23 13:01:20 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read	*init_data(void)
{
	t_read	*data;

	if (!(data = malloc(sizeof(t_read))))
		return (NULL);
	data->c = 0;
	data->pos = 0;
	data->len = 0;
	data->str = NULL;
	return (data);
}

int		ft_getc(void)
{
	int	c;

	c = 0;
	read(0, &c, sizeof(c));
	return (c);
}

int		get_last_char(void)
{
	int	c;
	struct termios	oterm;
	struct termios	term;

	tcgetattr(0, &oterm);
	memcpy(&term, &oterm, sizeof(term));
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	c = ft_getc();
	tcsetattr(0, TCSANOW, &oterm);
	return (c);
}