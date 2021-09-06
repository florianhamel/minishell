/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_def.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 22:05:40 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/06 17:14:23 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var_def_lst(t_data *data, t_var *var_def_lst)
{
	t_var	*current;
	t_var	*new_var;

	new_var = var_def_lst;
	while (new_var)
	{
		current = data->var_lst;
		while (current->next)
			current = current->next;
		new_var->prev = current;
		current->next = new_var;
		new_var = new_var->next;
	}
}

int	is_var_def(char *str)
{
	int	i;

	i = 1;
	if (!str[0] || !ft_isalpha(str[0]))
		return (0);
	while ((str[i] && ft_isalnum(str[i]) && !ft_is_ws(str[i])) || \
	str[i] == '=')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
	t_var	*current;
	t_var	*var_def;

	current = cmd->var_def_lst;
	var_def = malloc(sizeof(t_var));
	if (!var_def)
		exit_custom(data, NULL, AUTO);
	var_def->prev = NULL;
	var_def->next = NULL;
	var_def->name = get_var_def_name(data, pos);
	var_def->val = get_var_def_val(data, pos);
	if (!cmd->var_def_lst)
		cmd->var_def_lst = var_def;
	else
	{
		while (current->next)
			current = current->next;
		var_def->prev = current;
		current->next = var_def;
	}
}
