/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:53:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/14 15:36:20 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_syntax_error(t_data *data, int *pos, t_cmd *cmd)
{
	char	*serror;
	int		i;

	i = *pos;
	serror = "minishell: syntax error";
	if (data->str[i] == data->str[i - 1])
		i++;	
	i += skip_ws(&(data->str[i]));
	if (!data->str[i] || is_redir(data->str[i]) || data->str[i] == '|')
		exit_custom(data, serror, CUSTOM);
}

void	set_redir(t_data *data, int *pos, t_cmd *cmd)
{
	redir_syntax_error(data, pos, cmd);
	if (data->str[*pos] == '<')
	{
		cmd->flag_in = get_flag_in(data, pos);
		cmd->infile = get_file_cmd(data, pos);
		if (cmd->flag_in == DOUBLE_LEFT)
			cmd->word = get_word(data, pos);
	}
	else
	{
		cmd->flag_out = get_flag_out(data, pos);
		cmd->outfile = get_file_cmd(data, pos);
	}
}
