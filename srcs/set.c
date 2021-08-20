/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:53:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/19 20:29:55 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_data *data, int flag)
{
	data->status = 2;
	if (flag == REDIR)
		printf("%s\n", "minishell: redirection syntax error");
	else if (flag == PIPE)
		printf("%s\n", "minishell: pipe syntax error");
	else
		printf("%s\n", "minishell: syntax error");
	return (ERROR);
}

int	check_syntax_error(t_data *data)
{
	int	i;

	i = 0;
	while (data->str[i])
	{
		if (is_redir(data->str[i]))
		{
			i++;
			if (data->str[i] == data->str[i - 1])
				i++;
			i += skip_ws(&data->str[i]);
			if (!data->str[i] || is_redir(data->str[i]) || data->str[i] == '|')
				return (syntax_error(data, REDIR));
		}
		else if (data->str[i] == '|')
		{
			i++;
			i += skip_ws(&data->str[i]);
			if (!data->str[i])
				return (syntax_error(data, PIPE));
		}
		i++;
	}
	return (SUCCESS);
}

void	set_redir(t_data *data, int *pos, t_cmd *cmd)
{
	if (data->str[*pos] == '<')
	{
		cmd->flag_in = get_flag_in(data, pos);
		if (cmd->flag_in == DOUBLE_LEFT)
			cmd->word = get_word(data, pos);
		else
			cmd->infile = get_arg(data, pos);
	}
	else
	{
		cmd->flag_out = get_flag_out(data, pos);
		cmd->outfile = get_arg(data, pos);
	}
}

void	set_args(t_data *data, int *pos, t_cmd *cmd)
{
	char	*var_val;

	var_val = NULL;
	while (data->str[*pos] && !is_redir(data->str[*pos]) && \
	data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
		{
			var_val = get_var(data, pos);
			if (var_val)
				cmd->args = concat_str(data, cmd->args, var_val);
			else
				return ;
		}
		else if (is_quote(data->str[*pos]) && is_closed_quote(data, pos))
			cmd->args = concat_str(data, cmd->args, get_quote(data, pos));
		else
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
	}
}
