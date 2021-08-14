/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:11:08 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/14 15:36:33 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(t_data *data, int *pos)
{
	char	*var_name;

	var_name = NULL;
	while (data->str[*pos] && !is_ws(data->str[*pos]))
	{
		var_name = add_char(var_name, data->str[*pos]);
		if (!var_name)
			exit_custom(data, NULL, NOT_CUSTOM);
		(*pos)++;
	}
	return (var_name);
}

int	find_var_env(t_data *data, int *pos, char *var_name)
{
	char	*var_env;
	int		i;
	int		j;

	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
		{
			var_env = add_char(var_env, data->env[i][j]);
			j++;
		}
		if (!ft_strncmp(var_name, var_env, ft_strlen(var_name) + 1))
			return (i);
		i++;
	}
	return (NOT_FOUND);
}

char	*get_var_val(t_data *data, int *pos)
{
	char	*var_name;
	char	*var_val;
	int		i;
	int		j;

	var_name = get_var_name(data, pos);
	var_val = NULL;
	i = find_var(data, pos, var_name);
	j = 0;
	free_null((void **)&var_name);
	if (i == NOT_FOUND)
		return (NULL);
	while (data->env[i][j] && data->env[i][j] != '=')
		j++;
	j++;
	while (data->env[i][j])
	{
		var_val = add_char(var_val, data->env[i][j]);
		if (!var_val)
			exit_custom(data, NULL, NOT_CUSTOM);
		j++;
	}
	return (var_val);
}
