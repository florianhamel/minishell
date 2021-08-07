/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/08/06 17:26:39 by fhamel           ###   ########.fr       */
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
	char		*str;

	status = 0;
	history = get_history(20);
	while (1)
	{
		intro();
		str = get_cmd(&history, &status);
		// execute_cmd(str, &status);
		ft_free((void **)&str);
	}
}

int		main(void)
{
	minishell();
	return (0);
}
