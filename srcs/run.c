/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/06 15:26:41 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_sig	g_data;

void	stop_process(int signum)
{
	if (signum == SIGINT)
	{	
		if (g_data.pid > 0)
		{	
			kill(g_data.pid, SIGINT);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	else if (signum == SIGQUIT)
	{
		if (g_data.pid > 0)
		{
			kill(g_data.pid, SIGQUIT);
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		}
	}	
}

void	add_var_def_lst(t_data *data, t_var *var_def_lst)
{
	t_var	*current;
	t_var	*new_var;

	new_var = var_def_lst;
	while (new_var)
	{
		current = data->var_lst;
		while (current->next)
			current = current->next;
		new_var->prev = current;
		current->next = new_var;
		new_var = new_var->next;
	}
}

int	run_cmd(t_data *data, t_cmd *cmd, int fd_pipe)
{
	t_run	run;

	run.fd_pipe = fd_pipe;
	run.fd_in = NO_FD;
	run.fd_out = NO_FD;
	if (pipe(run.fd) == ERROR)
		exit_custom(data, NULL, AUTO);
	g_data.pid = fork();
	if (g_data.pid == ERROR)
		exit_custom(data, NULL, AUTO);
	if (g_data.pid == CHILD)
		call(data, cmd, run);
	if (fd_pipe != NO_FD)
		close(fd_pipe);
	close(run.fd[1]);
	waitpid(g_data.pid, &run.status, 0);
	data->status = WEXITSTATUS(run.status);
	return (run.fd[0]);
}

void	run(t_data *data)
{
	int		fd_pipe;
	t_cmd	*current;

	if (check_syntax_error(data) == ERROR)
		return ;
	data->cmd_lst = get_cmd_lst(data);
	fd_pipe = NO_FD;
	current = data->cmd_lst;
	while (current)
	{
		if (current->var_def_lst && !current->args)
			add_var_def_lst(data, current->var_def_lst);
		fd_pipe = run_cmd(data, current, fd_pipe);
		if (data->status == 130)
			break ;
		current = current->next;
	}
	free_cmd_lst(data);
	free_null((void **)&data->str);
}
