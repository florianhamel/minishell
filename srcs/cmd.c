/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:56:07 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/16 15:44:24 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_elem_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit_custom(data, NULL, NOT_CUSTOM);
	return (NULL);
}

void	append_cmd(t_cmd **cmd_lst, t_cmd *cmd)
{
	if (!(*cmd_lst))
		*cmd_lst = cmd;
	else
	{}
}

t_cmd	*get_cmd_lst(t_data *data)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = skip_ws(&(data->str[0]));
	while (data->str[i])
	{
		cmd = new_elem_cmd(data);
		while (data->str[i] && data->str[i] != '|')
		{
			if (is_redir(data->str[i]))
				set_redir(data, &i, cmd);
			else
				set_cmd(data, &i, cmd);
		}
		if (data->str[i] == '|')
			i++;
		append_cmd(&cmd_lst, cmd);
	}
	return (cmd_lst);
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		free_null((void **)&(cmd->infile));
		free_null((void **)&(cmd->outfile));
		free_null((void **)&(cmd->cmd));
		free_null((void **)&(cmd->options));
		free_null((void **)&(cmd->word));
		free_null((void **)&cmd);
		cmd = next;
	}
}

void	execute_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = get_cmd_lst(data);
	
}
