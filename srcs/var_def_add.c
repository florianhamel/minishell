/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_def.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:25:43 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/09 17:57:19 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_var_def(t_var *var_def, t_data *data)
{
	t_var	*new_var;
	t_var	*current;

	current = data->var_lst;
	while (current->next)
		current = current->next;
	new_var = malloc(sizeof(t_var));
	if (!new_var)
		exit_custom(data, NULL, AUTO);
	new_var->prev = current;
	new_var->next = NULL;
	new_var->name = ft_strdup(var_def->name);
	new_var->val = ft_strdup(var_def->val);
	current->next = new_var;
}

void	add_var_def_lst(t_data *data, t_var *var_def_lst)
{
	t_var	*var_def;

	var_def = var_def_lst;
	while (var_def)
	{
		append_var_def(var_def, data);
		var_def = var_def->next;
	}
}

void	free_var_def_lst(t_var *var_def_lst)
{
	t_var	*var_def;
	t_var	*next;

	var_def = var_def_lst;
	while (var_def)
	{
		next = var_def->next;
		free_null((void **)&var_def->name);
		free_null((void **)&var_def->val);
		free_null((void **)&var_def);
		var_def = next;
	}
}
