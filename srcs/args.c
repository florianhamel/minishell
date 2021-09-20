/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:42:13 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/19 19:42:14 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**realloc_args(t_data *data, char **args, int index)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * (index + 2));
	if (!new_args)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = NULL;
	new_args[i + 1] = NULL;
	free(args);
	args = NULL;
	return (new_args);
}

char	**get_args(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		index;
	int		j;

	if (!cmd->args)
		return (NULL);
	args = NULL;
	index = 0;
	j = skip_ws(&cmd->args[0]);
	while (cmd->args[j])
	{
		args = realloc_args(data, args, index);
		while (cmd->args[j] && !ft_is_ws(cmd->args[j]))
		{
			if (check_quote(cmd->args, j))
				args[index] = concat_str(data, args[index], \
				get_quote(data, cmd->args, &j));
			else
				args[index] = add_char(data, args[index], cmd->args[j++]);
		}
		j += skip_ws(&cmd->args[j]);
		index++;
	}
	return (args);
}
