/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:25:22 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/13 14:03:39 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_slash_in(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int	is_direct_path(char *name)
{
	struct stat	statbuf;

	if (check_slash_in(name))
		if (stat(name, &statbuf) == SUCCESS)
			return (1);
	return (0);
}

char	*concat_path_bin(t_data *data, char *path, char *bin)
{
	char	*path_bin;
	int		i;
	int		j;

	path_bin = malloc(ft_strlen(path) + ft_strlen(bin) + 2);
	i = 0;
	j = 0;
	if (!path_bin)
		exit_custom(data, NULL, AUTO);
	while (path && path[i])
	{
		path_bin[i] = path[i];
		i++;
	}
	path_bin[i] = '/';
	i++;
	while (bin && bin[j])
	{
		path_bin[i] = bin[j];
		i++;
		j++;
	}
	path_bin[i] = '\0';
	return (path_bin);
}

char	*get_var_path(t_data *data)
{
	char	*var_path;
	t_var	*current;

	var_path = NULL;
	current = data->var_lst;
	while(current)
	{
		if (!ft_strncmp("PATH", current->name, 5) && current->val)
		{
			var_path = ft_strdup(current->val);
			if (!var_path)
				exit_custom(data, NULL, AUTO);
			return (ft_strdup(var_path));
		}
		current = current->next;
	}
	return (var_path);
}
