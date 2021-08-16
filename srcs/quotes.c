/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:13:27 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/16 16:27:25 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quote_word(t_data *data, int *pos)
{
	data = (t_data *)data;
	pos = (int  *)pos;
	return (NULL);
}

char	*get_simple_quote(t_data *data,  int *pos)
{
	char	*quote;

	quote = NULL;
	while (data->str[*pos] && data->str[*pos] != '\'')
	{
		add_char(quote, data->str[*pos]);
		(*pos)++;
	}
	if (data->str[*pos] == '\'')
		(*pos)++;
	return (quote);
}

char	*get_double_quote(t_data *data, int *pos)
{
	char	*quote;

	quote = NULL;
	while (data->str[*pos] && data->str[*pos] != '\"')
	{
		if (data->str[*pos] == '$')
			quote = concat_str(quote, get_var_val(data, pos));
		else
		{
			add_char(quote, data->str[*pos]);
			(*pos)++;
		}
	}
	if (data->str[*pos] == '\"')
		(*pos)++;
	return (quote);
}

char	*get_quote(t_data *data, int *pos)
{
	char	*quote;

	(*pos)++;
	if (data->str[*pos] == '\'')
		quote = get_simple_quote(data, pos);
	else
		quote = get_double_quote(data, pos);
	return (quote);
}
