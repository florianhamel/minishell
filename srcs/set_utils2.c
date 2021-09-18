/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:59:40 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/18 17:04:30 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file_word(t_data *data, int *pos)
{
	char	*arg;
	char	*var_val;

	arg = NULL;
	var_val = NULL;
	*pos += skip_ws(&data->str[*pos]);
	while (data->str[*pos] && !ft_is_ws(data->str[*pos]) && \
	!is_redir(data->str[*pos]) && data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
		{
			var_val = get_var(data, data->str, pos);
			if (var_val)
				arg = concat_str(data, arg, var_val);
		}
		else if (check_quote(data->str, *pos))
			arg = concat_str(data, arg, get_quote(data, data->str, pos));
		else
			arg = add_char(data, arg, data->str[(*pos)++]);
	}
	return (arg);
}

char	*get_word(t_data *data, int *pos)
{
	char	*word;
	char	*var_val;

	word = NULL;
	var_val = NULL;
	*pos += skip_ws(&data->str[*pos]);
	while (data->str[*pos] && !ft_is_ws(data->str[*pos]) && \
	!is_redir(data->str[*pos]) && data->str[*pos] != '|')
	{
		if (data->str[*pos] == '$')
		{
			var_val = get_var(data, data->str, pos);
			if (var_val)
				word = concat_str(data, word, var_val);
			else
				return (word);
		}
		else if (check_quote(data->str, *pos))
			word = concat_str(data, word, get_quote_word(data, pos));
		else
			word = add_char(data, word, data->str[(*pos)++]);
	}	
	return (word);
}

void	free_redir_lst(t_redir *redir)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir->prev)
		redir = redir->prev;
	while (redir)
	{
		next = redir->next;
		free_null((void **)&redir->word);
		free_null((void **)&redir);
		redir = next;
	}
}
