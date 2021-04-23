/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/04/21 18:51:14 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			intro(void)
{
	write(1, "minishell$ ", 11);
}

char	*get_cmd(void)
{
	char	*str;

	while (1)
	{
		intro();
		if (!(str = read_mgmt()))
			return (NULL);
	}
}

void			minishell(void)
{
	char	*str;

	if (!(str = get_cmd()))
		exit (0);
}

int		main(void)
{
	minishell();
	return (0);
}
