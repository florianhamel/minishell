/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:51:42 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/19 13:40:34 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		is_closed_quote(t_data *data, int *pos)
{
	int	char_quote;
	int	i;

	char_quote = data->str[*pos];
	i = *pos + 1;
	while (data->str[i])
	{
		if (data->str[i] == char_quote)
			return (1);
		i++;
	}
	return (0);
}

int	is_end_arg(int c)
{
	if (c && !ft_is_ws(c) && !is_redir(c) && c != '|')
		return (1);
	return (0);
}
