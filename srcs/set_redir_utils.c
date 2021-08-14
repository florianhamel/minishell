/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 11:50:28 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/14 03:01:40 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

int		get_flag_in(t_data *data, int *pos, t_cmd *cmd)
{
	(*pos)++;
	if (data->str[*pos] == '<')
	{
		(*pos)++;
		return (DOUBLE_LEFT);
	}
	return (SIMPLE_LEFT);
}

int		get_flag_out(t_data *data, int *pos, t_cmd *cmd)
{
	(*pos)++;
	if (data->str[*pos] == '>')
	{
		(*pos)++;
		return (DOUBLE_RIGHT);
	}
	return (SIMPLE_RIGHT);
}

char	*get_infile(t_data *data, int *pos)
{
	char	*infile;
	int		i;

	*pos += skip_ws(&data->str[*pos]);
	while (data->str[*pos])
	{
		// concat avec $ ou "" si jamais y'a XD
		if (data->str[*pos] == '$')
			infile = get_var_val(data, ++(*pos));
		if (is_quote(data->str[*pos]) && is_closed_quote((data, *pos)))
			infile = get_quote_value(data, *pos);
	}
}

char	*get_outfile(t_data *data, int *pos)
{
	char	*outfile;

	*pos += skip_ws(&data->str[*pos]);
	if (data->str[*pos] == '$')
		outfile = get_var_val(data, ++(*pos));
	if (is_quote(data->str[*pos]) && is_closed_quote((data, *pos)))
		outfile = get_quote_value(data, *pos);
}

char	*get_word(t_data *data, int *pos)
{
	(*pos)++;
	*pos += skip_ws(&data->str[*pos]);

}