/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/03 16:11:31 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	glob_pid;

void	handler(int signum)
{
	if (signum == SIGINT)
	{	
		if (glob_pid > 0)
		{	
			kill(glob_pid, SIGINT);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
	}
	else if (signum == SIGQUIT)
	{
		if (glob_pid > 0)
		{
			kill(glob_pid, SIGQUIT);
			ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		}
	}	
}

int	run_cmd(t_data *data, t_cmd *cmd, int fd_pipe)
{
	t_run	run;

	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	run.fd_pipe = fd_pipe;
	run.fd_in = NO_FD;
	run.fd_out = NO_FD;
	if (pipe(run.fd) == ERROR)
		exit_custom(data, NULL, AUTO);
	run.pid = fork();
	glob_pid = run.pid;
	if (run.pid == ERROR)
		exit_custom(data, NULL, AUTO);
	if (run.pid == CHILD)
		call(data, cmd, run);
	if (fd_pipe != NO_FD)
		close(fd_pipe);
	close(run.fd[1]);
	waitpid(run.pid, &run.status, 0);
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
		fd_pipe = run_cmd(data, current, fd_pipe);
		current = current->next;
	}
	free_cmd_lst(data);
	free_null((void **)&data->str);
}
