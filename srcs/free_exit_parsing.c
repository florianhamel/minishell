/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:48:42 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/17 18:37:43 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_null(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	exit_strerror(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

void	free_parsing(t_read *data)
{
	free_history(data->current);
	free_data(data->data);
	free_null((void **)&(data->str));
	free_null((void **)&data);
}

void	exit_parsing(t_read *data)
{
	free_parsing(data);
	exit_strerror();
}
