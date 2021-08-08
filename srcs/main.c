/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/08/08 00:42:18 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			intro(void)
{
	write(1, "minishell$ ", 11);
}

void			minishell(void)
{
	int			status;
	t_history	*history;
	t_read		*data;

	status = 0;
	history = get_history(20);
	push_front(new_elem_history(NULL), &history);
	while (1)
	{
		intro();
		data = get_cmd(&history, &status);
		// execute_cmd(str, &status);
		ft_free((void **)&(data->str));
		ft_free((void **)&data);
	}
}

int		main(void)
{
	minishell();
	return (0);
}
