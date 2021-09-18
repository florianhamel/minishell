/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 14:03:44 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/18 11:05:50 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_env(t_data *data)
{
	t_var	*current;
	int		i;

	current = data->var_lst;
	i = 0;
	while (current)
	{
		if (current->flag == ENV)
			i++;
		current = current->next;
	}
	return (i);
}

char	*get_env_line(t_data *data, t_var *var)
{
	char	*env_line;
	int		i;

	env_line = NULL;
	i = 0;
	while (var->name && var->name[i])
		env_line = add_char(data, env_line, var->name[i++]);
	env_line = add_char(data, env_line, '=');
	i = 0;
	while (var->val && var->val[i])
		env_line = add_char(data, env_line, var->val[i++]);
	return (env_line);
}

char	**get_env(t_data *data)
{
	t_var	*current;
	char	**env;
	int		i;

	env = malloc(sizeof(char *) * (get_len_env(data) + 1));
	if (!env)
		exit_custom(data, NULL, AUTO);
	current = data->var_lst;
	i = 0;
	while (current)
	{
		if (current->flag == ENV)
		{
			env[i] = get_env_line(data, current);
			i++;
		}
		current = current->next;
	}
	env[i] = NULL;
	return (env);
}
