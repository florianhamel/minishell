/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:28:30 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/29 13:57:00 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup2_close(int new_fd, int old_fd)
{
	dup2(new_fd, old_fd);
	close(new_fd);
}

int	is_built_in(t_data *data, t_cmd *cmd)
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
