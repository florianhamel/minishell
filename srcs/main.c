/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/08/09 16:39:12 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intro(void)
{
	write(1, "minishell$ ", 11);
}

void	minishell(void)
{
	int			status;
	t_history	*history;
	t_read		*data;

	history = get_history(20);
	while (1)
	{
		status = 0;
		intro();
		data = get_cmd(&history, &status);
		if (!ft_strncmp(data->str, "exit", 5))
		{
			free_parsing(data);
			exit(0);
		}
		free_null((void **)&(data->str));
		free_null((void **)&data);
	}
}

int	main(void)
{
	minishell();
	return (0);
}
