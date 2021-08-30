/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:58:45 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/30 01:59:16 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*concat_path_bin(t_data *data, char *s1, char *s2)
{
	char	*path_bin;
	int		i;
	int		j;

	path_bin = malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	i = 0;
	j = 0;
	if (!path_bin)
		exit_custom(data, NULL, AUTO);
	while (s1 && s1[i])
	{
		path_bin[i] = s1[i];
		i++;
	}
	path_bin[i] = '/';
	i++;
	while (s2 && s2[j])
	{
		path_bin[i] = s2[j];
		i++;
		j++;
	}
	path_bin[i] = '\0';
	return (path_bin);
}

char	*get_path_bin(t_data *data, char *name, char *var_path)
{
	char		*path_bin;
	char		**arr_path;
	struct stat	statbuf;
	int			i;

	path_bin = NULL;
	arr_path = ft_split(var_path, ':');
	if (!arr_path)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (arr_path[i])
	{
		path_bin = concat_path_bin(data, arr_path[i], name);
		if (stat(path_bin, &statbuf) == SUCCESS)
		{
			ft_free_arr(arr_path);
			return (path_bin);
		}
		i++;
	}
	ft_free_arr(arr_path);
	free_null((void **)&path_bin);
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

char	*get_bin(t_data *data, char *name)
{
	char	*var_path;
	char	*path_bin;

	path_bin = NULL;
	var_path = get_var_path(data);
	if (var_path)
		path_bin = get_path_bin(data, name, var_path);
	free_null((void **)&var_path);
	return (path_bin);	
}

char	**get_argv(t_data *data, t_cmd *cmd)
{
	char		**argv;
	char		*bin;
	struct stat	statbuf;

	argv = NULL;
	if (!cmd->args)
		return (argv);
	if (cmd->args)
	{
		argv = ft_split(cmd->args, ' ');
		if (!argv)
			exit_custom(data, NULL, AUTO);
	}
	if (stat(argv[0], &statbuf) == SUCCESS)
		return (argv);
	bin = get_bin(data, argv[0]);
	free_null((void **)&argv[0]);
	argv[0] = bin;
	return (argv);
}
