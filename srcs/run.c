/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/31 02:18:16 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	call_built_in(t_data *data, t_cmd *cmd)
// {
// 	if (!ft_strncmp("echo", data->str, 4))
// 		data->status = ft_echo(data, cmd);
// 	else if (!ft_strncmp("cd", data->str, 2))
// 		data->status = ft_cd(data, cmd);
// 	else if (!ft_strncmp("pwd", data->str, 3))
// 		data->status = ft_pwd(data, cmd);
// 	else if (!ft_strncmp("export", data->str, 6))
// 		data->status = ft_export(data, cmd);
// 	else if (!ft_strncmp("unset", data->str, 5))
// 		data->status = ft_unset(data, cmd);
// 	else if (!ft_strncmp("env", data->str, 3))
// 		data->status = ft_env(data, cmd);
// 	else if (!ft_strncmp("exit", data->str, 4))
// 		data->status = ft_exit(data, cmd);
// }

void	call_execve(t_data *data, t_cmd *cmd)
{
	char	**argv;

	argv = get_argv(data, cmd);
	if (argv)
		if (execve(argv[0], argv, data->env) == ERROR)
			exit_custom(data, NULL, AUTO);
}

void	call(t_data *data, t_cmd *cmd, t_run run)
{
	run.fd_in = get_infile(data, cmd);
	run.fd_out = get_outfile(data, cmd);
	if (run.fd_pipe != NO_FD)
		dup2_close(run.fd_pipe, 0);
	if (cmd->next)
		dup2_close(run.fd[1], 1);
	if (run.fd_in != NO_FD)
		dup2_close(run.fd_in, 0);
	if (run.fd_out != NO_FD)
		dup2_close(run.fd_out, 1);
	if (!cmd->args)
	{
		free_history(data->history);
		free_data(data);
		exit(0);
	}
	call_execve(data, cmd);
	// is_built_in ?
	// call_built_in | call_execve
}

int	run_cmd(t_data *data, t_cmd *cmd, int fd_pipe)
{
	t_run	run;

	run.fd_pipe = fd_pipe;
	run.fd_in = NO_FD;
	run.fd_out = NO_FD;
	if (pipe(run.fd) == ERROR)
		exit_custom(data, NULL, AUTO);
	run.pid = fork();
	if (run.pid == ERROR)
		exit_custom(data, NULL, AUTO);
	if (run.pid == CHILD)
		call(data, cmd, run);
	if (fd_pipe > -1)
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
