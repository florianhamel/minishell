/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 01:51:19 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/18 11:35:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_pid;

void	check_tmp_dir(void)
{
	DIR	*dir;

	dir = opendir("/tmp");
	if (dir == NULL)
	{
		ft_putstr_fd("minishell: '/tmp' was not found\n", STDERR_FILENO);
		exit(1);
	}
	closedir(dir);
}

t_data	*init_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_strerror();
	data->var_lst = get_var_lst(data, env);
	data->str = NULL;
	data->status = 0;
	data->cmd_lst = NULL;
	data->history = get_history(20);
	return (data);
}

void	minishell(char **env)
{
	t_data		*data;
	t_read		*data_parsing;

	check_tmp_dir();
	data = init_data(env);
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
