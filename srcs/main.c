/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/06/04 17:20:24 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			intro(void)
{
	write(1, "minishell$ ", 11);
}

// char	*get_cmd(void)
// {
// 	char		*str;
// 	t_history	*history;

// 	history = get_history(20);
// 	while (1)
// 	{
// 		intro();
// 		if (!(str = read_mgmt(&history)))
// 			return (NULL);
		
// 	}
// }

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
		ft_free(str);
	}
}

int		main(void)
{
	minishell();
	return (0);
}
