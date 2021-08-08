/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 12:01:03 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/07 13:25:24 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_history *elem)
{
	t_history	*next;

	while (elem->prev)
		elem = elem->prev;
	while (elem)
	{
		next = elem->next;
		ft_free((void **)&(elem->cmd));
		ft_free((void **)&elem);
		elem = next;
	}
}