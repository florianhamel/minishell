/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:05:36 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/16 18:08:56 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_env(t_data *data, char *var_name)
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

char	*search_env(t_data *data, char *var_name)
{
	char	*var_val;
	int		i;
	int		j;

	var_val = NULL;
	i = find_var_env(data, var_name);
	j = 0;
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
