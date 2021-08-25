/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/24 16:50:40 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_data *data)
{
	// t_cmd	*current;

	if (check_syntax_error(data) == ERROR)
		return ;
	data->cmd_lst = get_cmd_lst(data);
	// current = data->cmd_lst;
	// while (current)
	// {
	// 	run_cmd(current);
	// 	current = current->next;
	// }
	print_cmd(data);
	free_cmd_lst(data);
	free_null((void **)&data->str);
}
