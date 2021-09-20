/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:53:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/19 19:39:39 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redir(t_data *data, int *pos, t_cmd *cmd)
{
	if (data->str[*pos] == '<')
		set_redir_in(data, pos, cmd);
	else
		set_redir_out(data, pos, cmd);
}

void	set_args(t_data *data, int *pos, t_cmd *cmd)
{
	char	*var_val;
	int		quote_type;

	var_val = NULL;
	while (data->str[*pos] && !is_redir(data->str[*pos]) && \
	data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
			cmd->args = concat_str(data, cmd->args, \
			get_var(data, data->str, pos));
		else if (check_quote(data->str, *pos))
		{
			quote_type = data->str[*pos];
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
			while (data->str[*pos] && data->str[*pos] != quote_type)
				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
			if (data->str[*pos] == quote_type)
				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
		}
		else
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
	}
}
