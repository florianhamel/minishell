/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/18 14:29:56 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_pid;

int	get_status_error(int signum)
{
	if (signum == SIGINT)
		return (130);
	if (signum == SIGQUIT)
		return (131);
	return (0);
}

void	stop_process(int signum)
{
	if (signum == SIGINT)
	{
		if (g_pid > 0)
		{	
			kill(g_pid, SIGINT);
			ft_putchar_fd('\n', STDERR_FILENO);
		}
	}
	else if (signum == SIGQUIT)
	{
		if (g_pid > 0)
		{
			kill(g_pid, SIGQUIT);
			ft_putstr_fd("Quit\n", STDERR_FILENO);
		}
	}	
}

int	run_builtin(t_data *data, t_cmd *cmd, int fd_pipe)
{
	t_run	run;

	run.fd_pipe = fd_pipe;
	run.fd_in = dup(STDIN_FILENO);
	run.fd_out = dup(STDOUT_FILENO);
	if (pipe(run.fd) == ERROR)
		exit_custom(data, NULL, AUTO);
	data->status = call_builtin(data, cmd, run);
	if (fd_pipe != NO_FD)
		close(fd_pipe);
	dup2(run.fd_in, STDIN_FILENO);
	dup2(run.fd_out, STDOUT_FILENO);
	return (run.fd[0]);
}

int	run_execve(t_data *data, t_cmd *cmd, int fd_pipe)
{
	t_run	run;

	run.fd_pipe = fd_pipe;
	run.fd_in = NO_FD;
	run.fd_out = NO_FD;
	if (pipe(run.fd) == ERROR)
		exit_custom(data, NULL, AUTO);
	g_pid = fork();
	if (g_pid == ERROR)
		exit_custom(data, NULL, AUTO);
	if (g_pid == CHILD)
		call_execve(data, cmd, run);
	if (fd_pipe != NO_FD)
		close(fd_pipe);
	close(run.fd[1]);
	waitpid(g_pid, &run.status, 0);
	if (WIFSIGNALED(run.status))
		data->status = get_status_error(WTERMSIG(run.status));
	else
		data->status = WEXITSTATUS(run.status);
	return (run.fd[0]);
}

void	run(t_data *data)
{
	int		fd_pipe;
	t_cmd	*current;

	if (check_syntax_error(data) == ERROR)
	{
		free_null((void **)&data->str);
		return ;
	}
	data->cmd_lst = get_cmd_lst(data);
	fd_pipe = NO_FD;
	current = data->cmd_lst;
	while (current)
	{
		if (is_builtin(data, current))
			fd_pipe = run_builtin(data, current, fd_pipe);
		else
			fd_pipe = run_execve(data, current, fd_pipe);
		if (data->status == 130)
			break ;
		current = current->next;
	}
	free_cmd_lst(data);
	free_null((void **)&data->str);
}
