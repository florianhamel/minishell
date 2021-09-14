/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:56:07 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/14 12:24:51 by fhamel           ###   ########.fr       */
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
	elem->in_lst = NULL;
	elem->out_lst = NULL;
	elem->args = NULL;
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

void	append_cmd(t_cmd **cmd_lst, t_cmd *cmd)
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

void	free_cmd_lst(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*next;

	cmd = data->cmd_lst;
	if (!cmd)
		return ;
	while (cmd->prev)
		cmd = cmd->prev;
	while (cmd)
	{
		next = cmd->next;
		free_redir_lst(cmd->in_lst);
		cmd->in_lst = NULL;
		free_redir_lst(cmd->out_lst);
		cmd->out_lst = NULL;
		free_null((void **)&(cmd->args));
		free_null((void **)&cmd);
		cmd = next;
	}
	data->cmd_lst = NULL;
}

// fonction de test

void	print_redir_lst(t_redir *redir)
{
	if (!redir)
	{
		printf("%p$\n", redir);
		return ;
	}
	while (redir)
	{
		printf("flag: %d$\n", redir->flag);
		printf("word: %s$\n", redir->word);
		printf("\n");
		redir = redir->next;
	}
}

void	print_cmd(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_lst;
	while (current)
	{
		printf("----------ELEM----------\n");
		printf("***** in_lst ******\n");
		print_redir_lst(current->in_lst);
		printf("***** out_lst ******\n");
		print_redir_lst(current->out_lst);
		printf("arg: %s$\n", current->args);
		printf("prev: %p$\n", current->prev);
		printf("next: %p$\n", current->next);
		current = current->next;
	}
}

t_cmd	*get_cmd_lst(t_data *data)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd_lst = NULL;
	i = 0;
	while (data->str[i])
	{
		cmd = new_elem_cmd(data);
		append_cmd(&cmd_lst, cmd);
		while (data->str[i] && data->str[i] != '|')
		{
			i += skip_ws(&data->str[i]);
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
