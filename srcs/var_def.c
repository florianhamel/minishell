/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_def.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:05:40 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/14 10:20:50 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_def_name(t_data *data, int *pos)
{
	char	*var_def_name;

	var_def_name = NULL;
	while (data->str[*pos] && data->str[*pos] != '=')
	{
		var_def_name = add_char(data, var_def_name, data->str[*pos]);
		(*pos)++;
	}
	return (var_def_name);
}

char	*get_var_def_val(t_data *data, int *pos)
{
	char	*var_def_val;
	char	*var_val;

	var_def_val = NULL;
	var_val = NULL;
	(*pos)++;
	while (data->str[*pos] && !ft_is_ws(data->str[*pos]))
	{
		if (data->str[*pos] == '$')
			var_def_val = concat_str(data, var_def_val, get_var(data, pos));
		else if (is_quote(data->str[*pos]) && is_closed_quote(data, pos))
			var_def_val = concat_str(data, var_def_val, get_quote(data, pos));
		else
			var_def_val = add_char(data, var_def_val, data->str[(*pos)++]);
	}
	return (var_def_val);
}

void	set_var_def(t_data *data, int *pos, t_cmd *cmd)
{
	char	*name;
	char	*val;
	t_var	*current;

	name = get_var_def_name(data, pos);
	val = get_var_def_val(data, pos);
	current = data->var_lst;
	while (current && ft_strncmp(name, current->name, ft_strlen(name) + 1))
		current = current->next;
	if (current && (current->flag == EXP_NO_DEF || current->flag == EXP_DEF))
	{
		current->flag = 
		modify_var_def(data, cmd, name, val);
	}
	else if (current && current->flag == LOCAL)
		modify_var_def(data, cmd, name, val, LOCAL);
	else
		create_var(data, name, val, LOCAL);
	free_null((void **)&name);
	free_null((void **)&val);
}
