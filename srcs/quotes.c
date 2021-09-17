/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 13:13:27 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/17 22:13:17 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quote_word(t_data *data, int *pos)
{
	char	*quote;
	int		quote_char;

	quote = NULL;
	quote_char = data->str[*pos];
	(*pos)++;
	while (data->str[*pos] && data->str[*pos] != quote_char)
	{
		quote = add_char(data, quote, data->str[*pos]);
		(*pos)++;
	}
	if (data->str[*pos] == quote_char)
		(*pos)++;
	return (quote);
}

char	*get_simple_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	quote = NULL;
	while (str[*pos] && str[*pos] != '\'')
	{
		quote = add_char(data, quote, str[*pos]);
		(*pos)++;
	}
	if (str[*pos] == '\'')
		(*pos)++;
	return (quote);
}

char	*get_double_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	quote = NULL;
	while (str[*pos] && str[*pos] != '\"')
	{
		if (str[*pos] == '$')
			quote = concat_str(data, quote, get_var(data, str, pos));
		else
		{
			quote = add_char(data, quote, str[*pos]);
			(*pos)++;
		}
	}
	if (str[*pos] == '\"')
		(*pos)++;
	return (quote);
}

char	*get_quote(t_data *data, char *str, int *pos)
{
	char	*quote;

	if (str[(*pos)++] == '\'')
		quote = get_simple_quote(data, str, pos);
	else
		quote = get_double_quote(data, str, pos);
	return (quote);
}
