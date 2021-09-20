/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:57:08 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 03:00:43 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_var(t_data *data, char *arg)
{
	t_var	*current;

	current = data->var_lst;
	while (current)
	{
		if (!ft_strncmp(current->name, arg, ft_strlen(current->name) + 1))
		{
			if (current->next)
				current->next->prev = current->prev;
			if (current->prev)
				current->prev->next = current->next;
			free_null((void **)&current->name);
			free_null((void **)&current->val);
			free_null((void **)&current);
			return ;
		}
		current = current->next;
	}
}

int	ft_unset(t_data *data, char **args)
{
	int	status;
	int	i;

	status = 0;
	i = 1;
	if (args[1] && is_option(args[1]))
	{
		error_option(args[1], "export", &status);
		ft_free_arr(args);
		return (status);
	}
	while (args[i])
	{
		if (!data->cmd_lst->next && is_valid_var(args[i]))
			unset_var(data, args[i]);
		else if (!is_valid_var(args[i]))
			error_identifier(args[i], "unset", &status);
		i++;
	}
	ft_free_arr(args);
	return (status);
}
