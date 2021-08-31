/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:05:36 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/31 17:18:22 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_env(t_data *data, char *var_name)
{
	char	*var_env;
	int		i;
	int		j;

	var_env = NULL;
	i = 0;
	while (data->env[i])
	{
		j = 0;
		while (data->env[i][j] && data->env[i][j] != '=')
		{
			var_env = add_char(data, var_env, data->env[i][j]);
			j++;
		}
		if (!ft_strncmp(var_name, var_env, ft_strlen(var_name) + 1))
		{
			free_null((void **)&var_env);
			return (i);
		}
		free_null((void **)&var_env);
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
	if (data->env[i][j] == '=')
		j++;
	while (data->env[i][j])
	{
		var_val = add_char(data, var_val, data->env[i][j]);
		j++;
	}
	return (var_val);
}

char	*search_var_lst(t_data *data, char *var_name)
{
	t_var	*current;
	char	*var_val;

	current = data->var_lst;
	var_val = NULL;
	while (current)
	{
		if (!ft_strncmp(var_name, current->name, ft_strlen(var_name) + 1))
			var_val = ft_strdup(current->val);
		current = current->next;
	}
	return (var_val);
}
