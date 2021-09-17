/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 20:53:32 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/17 23:51:32 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_data *data, int flag)
{
	data->status = 2;
	if (flag == REDIR)
		ft_putstr_fd("minishell: redirection syntax error\n", STDERR_FILENO);
	else if (flag == PIPE)
		ft_putstr_fd("minishell: pipe syntax error\n", STDERR_FILENO);
	else
		ft_putstr_fd("minishell: syntax error\n", STDERR_FILENO);
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
		set_redir_in(data, pos, cmd);
	else
		set_redir_out(data, pos, cmd);
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
			cmd->args = concat_str(data, cmd->args, \
			get_var(data, data->str, pos));
		}
		else if (check_quote(data->str, *pos))
			while (data->str[*pos])
				cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
		else
			cmd->args = add_char(data, cmd->args, data->str[(*pos)++]);
	}
}
