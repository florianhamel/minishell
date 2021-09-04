/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 22:22:20 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/03 20:30:09 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile(t_data *data, t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->in_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_LEFT)
		{
			fd = open(current->word, O_RDONLY);
			if (fd == ERROR)
			{
				data->status = 1;
				exit_custom(data, ft_strdup(current->word), CUSTOM);
			}
		}
		else if (current->flag == DOUBLE_LEFT)
			fd = get_heredoc(data, current);
		current = current->next;
	}
	return (fd);
}

int	get_outfile(t_data *data, t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->out_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (current->flag == DOUBLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == ERROR)
		{
			data->status = 2;
			exit_custom(data, current->word, CUSTOM);
		}
		current = current->next;
	}
	return (fd);
}

