/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 12:48:04 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/20 00:41:41 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_data *data)
{
	// t_cmd	*current;

	// current = data->cmd_lst;
	// while (current)
	// {
	// 	run_cmd(current);
	// 	current = current->next;
	// }
	if (check_syntax_error(data) == ERROR)
		return ;
	data->cmd_lst = get_cmd_lst(data);
	// print_cmd(data);
	free_cmd_lst(data->cmd_lst);
	data->cmd_lst = NULL;
	free_null((void **)&data->str);
}
