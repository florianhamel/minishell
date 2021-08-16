/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:11:08 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/16 18:08:08 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(t_data *data, int *pos)
{
	char	*var_name;

	(*pos)++;
	var_name = NULL;
	while (data->str[*pos] &&\
	(ft_isalnum(data->str[*pos]) || data->str[*pos] == '_') &&\
	!ft_is_ws(data->str[*pos]))
	{
		var_name = add_char(var_name, data->str[*pos]);
		if (!var_name)
			exit_custom(data, NULL, NOT_CUSTOM);
		(*pos)++;
	}
	return (var_name);
}

char	*get_var_val(t_data *data, char *var_name)
{
	char	*var_val;

	var_val = search_var_lst(data, var_name);
	if (var_val)
		return (var_val);
	var_val = search_env(data, var_name);
	return (var_val);
}

char	*get_var(t_data *data, int *pos)
{
	char	*var_name;
	char	*var_val;

	var_name = get_var_name(data, pos);
	if (!var_name)
	{
		var_val = malloc(2);
		if (!var_val)
			exit_custom(data, NULL, NOT_CUSTOM);
		var_val[0] = '$';
		var_val[1] = '\0';
	}
	else
		var_val = get_var_val(data, var_name);
	free_null((void **)&var_name);
	return (var_val);
}
