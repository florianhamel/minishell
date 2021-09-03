/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:56:46 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/03 16:04:06 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup2_close(int new_fd, int old_fd)
{
	dup2(new_fd, old_fd);
	close(new_fd);
}

int	is_builtin(t_data *data, t_cmd *cmd)
{
	char	**args;

	if (!cmd->args)
		return (0);
	args = ft_split(cmd->args, ' ');
	if (!args)
		exit_custom(data, NULL, AUTO);
	if (!ft_strncmp("echo", args[0], 5) ||\
	!ft_strncmp("cd", args[0], 3) ||\
	!ft_strncmp("pwd", args[0], 4) ||\
	!ft_strncmp("export", args[0], 7) ||\
	!ft_strncmp("unset", args[0], 6) ||\
	!ft_strncmp("env", args[0], 4) ||\
	!ft_strncmp("exit", args[0], 5))
	{
		ft_free_arr(args);
		return (1);
	}
	ft_free_arr(args);
	return (0);
}

// void	call_builtin(t_data *data, t_cmd *cmd)
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
		dup2_close(run.fd_pipe, STDIN_FILENO);
	if (cmd->next)
		dup2_close(run.fd[1], STDOUT_FILENO);
	if (run.fd_in != NO_FD)
		dup2_close(run.fd_in, STDIN_FILENO);
	if (run.fd_out != NO_FD)
		dup2_close(run.fd_out, STDOUT_FILENO);
	if (!cmd->args)
	{
		free_history(data->history);
		free_data(data);
		exit(0);
	}
	// if (is_builtin(cmd))
	// 	call_builtin(data, cmd);
	call_execve(data, cmd);
}
