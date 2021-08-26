/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:58:45 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/25 16:05:47 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_argv(t_data *data, t_cmd *cmd)
{
	char	**argv;

	if (cmd->args)
		argv = ft_split(cmd->args);
	return (argv);
}