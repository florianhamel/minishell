/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 14:48:42 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/03 16:15:36 by fhamel           ###   ########.fr       */
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
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
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
