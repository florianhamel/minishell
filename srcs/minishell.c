/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:51:19 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/12 13:13:36 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_data;

void	intro(void)
{
	ft_putstr_fd("\033[0;37mminishell\033[0;92m$\033[0m ", 1);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_strerror();
	data->env = copy_env(data, env);
	data->str = NULL;
	data->status = 0;
	data->var_lst = init_var_lst(data);
	data->cmd_lst = NULL;
	data->history = get_history(20);
	return (data);
}

void	minishell(char **env)
{
	t_data		*data;
	t_read		*data_parsing;

	data = init_data(env);
	g_data.data = data;
	if (signal(SIGINT, stop_process) == SIG_ERR)
		exit_custom(data, NULL, AUTO);
	if (signal(SIGQUIT, stop_process) == SIG_ERR)
		exit_custom(data, NULL, AUTO);
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
