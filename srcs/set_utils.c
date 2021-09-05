/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:50:28 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/05 23:31:40 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_flag_in(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '<')
	{
		(*pos)++;
		return (DOUBLE_LEFT);
	}
	return (SIMPLE_LEFT);
}

int		get_flag_out(t_data *data, int *pos)
{
	(*pos)++;
	if (data->str[*pos] == '>')
	{
		(*pos)++;
		return (DOUBLE_RIGHT);
	}
	return (SIMPLE_RIGHT);
}

char	*get_word(t_data *data, int *pos)
{
	char	*word;
	char	*var_val;

	word = NULL;
	var_val = NULL;
	*pos += skip_ws(&data->str[*pos]);
	while (data->str[*pos] && !ft_is_ws(data->str[*pos]) && \
	!is_redir(data->str[*pos]) && data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
		{
			var_val = get_var(data, pos);
			if (var_val)
				word = concat_str(data, word, var_val);
			else
				return (word);
		}
		else if (is_quote(data->str[*pos]) && is_closed_quote(data, pos))
			word = concat_str(data, word, get_quote_word(data, pos));
		else
			word = add_char(data, word, data->str[(*pos)++]);
	}	
	return (word);
}

void	set_redir_in(t_data *data, int *pos, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*redir;

	current = cmd->in_lst;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit_custom(data, NULL, AUTO);
	redir->prev = NULL;
	redir->next = NULL;
	redir->flag = get_flag_in(data, pos);
	if (redir->flag == DOUBLE_LEFT)
		redir->word = get_word(data, pos);
	else
		redir->word = get_arg(data, pos);
	if (!cmd->in_lst)
		cmd->in_lst = redir;
	else
	{
		while (current->next)
			current = current->next;
		redir->prev = current;
		current->next = redir;
	}
}

void	set_redir_out(t_data *data, int *pos, t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*redir;

	current = cmd->out_lst;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit_custom(data, NULL, AUTO);
	redir->prev = NULL;
	redir->next = NULL;
	redir->flag = get_flag_out(data, pos);
	redir->word = get_arg(data, pos);
	if (!cmd->out_lst)
		cmd->out_lst = redir;
	else
	{
		while (current->next)
			current = current->next;
		redir->prev = current;
		current->next = redir;
	}
}
