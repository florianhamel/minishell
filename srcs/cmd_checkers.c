/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:51:42 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/13 12:20:43 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int	is_redir(int c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_quote(int c)
{
	if (c == '\"' || c == '\'')
		return (1);
	return (0);
}

int	is_closed_quotes(t_data *data, int *pos)
{
	
}

int	is_special_char(int c)
{
	if (is_redir(c) || is_quote(c) || c == '|' || c == '$')
		return (1);
	return (0);
}
