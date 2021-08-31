/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:36:36 by user42            #+#    #+#             */
/*   Updated: 2021/08/31 14:48:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intro(void)
{
	ft_putstr_fd("\033[0;37mminishell\033[0;92m$\033[0m ", 1);
}

t_data	*init_data()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_strerror();
	data->env = copy_env(data);
	data->str = NULL;
	data->status = 0;
	data->var_lst = init_var_lst(data);
	data->cmd_lst = NULL;
	data->history = get_history(20);
	return (data);
}

void	minishell(void)
{
	t_data		*data;
	t_read		*data_parsing;

	data = init_data();
	while (1)
	{
		intro();
		data_parsing = get_input(data);
		data->str = data_parsing->str;
		free_null((void **)&data_parsing);
		if (data->str)
			run(data);
		free_null((void **)&data->var_lst->val);
		data->var_lst->val = ft_itoa(data->status);
	}
}

int	main(void)
{
	minishell();
	return (0);
}
