/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:25:22 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/01 13:43:13 by fhamel           ###   ########.fr       */
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
	char	**arr;
	int		i;

	i = 0;
	while (data->env[i])
	{
		arr = ft_split(data->env[i], '=');
		if (!arr)
			exit_custom(data, NULL, AUTO);
		if (!ft_strncmp("PATH", arr[0], 5))
		{
			ft_free_arr(arr);
			return (ft_strdup(&data->env[i][5]));
		}
		ft_free_arr(arr);
		i++;
	}
	return (NULL);
}
