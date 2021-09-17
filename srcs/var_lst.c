/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 12:45:54 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/15 12:23:45 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*get_new_var(t_data *data, char *env_line)
{
	t_var	*var;
	int		i;

	var = malloc(sizeof(t_var));
	if (!var)
	{
		free_null((void **)&data);
		exit_strerror();
	}
	var->prev = NULL;
	var->next = NULL;
	var->name = NULL;
	var->val = NULL;
	var->flag = ENV;
	i = 0;
	while (env_line[i] && env_line[i] != '=')
		var->name = add_char(data, var->name, env_line[i++]);
	if (env_line[i] == '=')
		i++;
	while (env_line[i])
		var->val = add_char(data, var->val, env_line[i++]);
	return (var);
}

void	append_var(t_var *var_lst, t_var *new_var)
{
	t_var	*current;

	current = var_lst;
	while (current->next)
		current = current->next;
	new_var->prev = current;
	current->next = new_var;
}

t_var	*init_var_lst(t_data *data)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
	{
		free_null((void **)&data);
		exit_strerror();
	}
	var->prev = NULL;
	var->next = NULL;
	var->name = malloc(2);
	if (!var->name)
	{
		free_null((void **)&data);
		exit_strerror();
	}
	var->name[0] = '?';
	var->name[1] = '\0';
	var->val = ft_itoa(0);
	var->flag = SPECIAL;
	return (var);
}

t_var	*get_var_lst(t_data *data, char **env)
{
	t_var	*var_lst;
	t_var	*new_var;
	int		shlvl;
	int		i;

	i = 0;
	var_lst = init_var_lst(data);
	while (env[i])
	{
		new_var = get_new_var(data, env[i]);
		if (!ft_strncmp("SHLVL", new_var->name, 6))
		{
			shlvl = ft_atoi(new_var->val);
			free_null((void **)&new_var->val);
			new_var->val = ft_itoa(shlvl + 1);
		}
		append_var(var_lst, new_var);
		i++;
	}
	return (var_lst);
}
