/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:56:07 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/19 20:30:29 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_arg(t_data *data, int *pos)
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
			var_val = get_var(data, pos);
			if (var_val)
				arg = concat_str(data, arg, var_val);
			else
				return (arg);
		}
		else if (is_quote(data->str[*pos]) && is_closed_quote(data, pos))
			arg = concat_str(data, arg, get_quote(data, pos));
		else
			arg = add_char(data, arg, data->str[(*pos)++]);
	}
	return (arg);
}

t_cmd	*new_elem_cmd(t_data *data)
{
	t_cmd	*elem;

	elem = malloc(sizeof(t_cmd));
	if (!elem)
		exit_custom(data, NULL, AUTO);
	elem->infile = NULL;
	elem->outfile = NULL;
	elem->args = NULL;
	elem->word = NULL;
	elem->flag_in = 0;
	elem->flag_out = 0;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	append_cmd (t_cmd **cmd_lst, t_cmd *cmd)
{
	t_cmd	*current;

	if (!(*cmd_lst))
	{
		*cmd_lst = cmd;
		return ;
	}
	current = *cmd_lst;
	while (current->next)
		current = current->next;
	current->next = cmd;
	cmd->prev = current;
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*next;

	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		free_null((void **)&(cmd->infile));
		free_null((void **)&(cmd->outfile));
		free_null((void **)&(cmd->args));
		free_null((void **)&(cmd->word));
		free_null((void **)&cmd);
		cmd = next;
	}
}

// fonction de test
void	print_cmd(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_lst;
	while (current)
	{
		printf("----------ELEM----------\n");
		printf("infile: %s\n", current->infile);
		printf("outfile: %s\n", current->outfile);
		printf("arg: %s\n", current->args);
		printf("word: %s\n", current->word);
		printf("flag_in: %d\n", current->flag_in);
		printf("flag_out: %d\n", current->flag_out);
		printf("prev: %p\n", current->prev);
		printf("next: %p\n", current->next);
		current = current->next;
	}

}

t_cmd	*get_cmd_lst(t_data *data)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = skip_ws(&(data->str[0]));
	while (data->str[i])
	{
		cmd = new_elem_cmd(data);
		append_cmd(&cmd_lst, cmd);
		while (data->str[i] && data->str[i] != '|')
		{
			if (is_redir(data->str[i]))
				set_redir(data, &i, cmd);
			else
				set_args(data, &i, cmd);
		}
		if (data->str[i] == '|')
			i++;
	}
	return (cmd_lst);
}
