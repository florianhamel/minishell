/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:28:12 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/20 02:59:24 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_env_value(t_var *env, char *new_pwd, char *ex_pwd)
{
	t_var	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp("PWD", tmp->name, 4) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(new_pwd);
		}
		if (ft_strncmp("OLDPWD", tmp->name, 7) == 0)
		{
			free(tmp->val);
			tmp->val = ft_strdup(ex_pwd);
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_data *data, char **path)
{
	char	new_pwd[PATH_MAX_B];
	char	ex_pwd[PATH_MAX_B];
	int		status;

	status = 0;
	if (path[1] && is_option(path[1]))
		error_option(path[1], "cd", &status);
	else if (path[1] && path[2])
		error_cd_args(&status);
	else if (path[1] && check_stat_path(path[1]))
	{
		if (!data->cmd_lst->next && !getcwd(ex_pwd, PATH_MAX_B))
			error_cwd(&status);
		if (!data->cmd_lst->next && chdir(path[1]) == ERROR)
			error_path(path[1], &status);
		if (!data->cmd_lst->next && !getcwd(new_pwd, PATH_MAX_B))
			error_cwd(&status);
		edit_env_value(data->var_lst, new_pwd, ex_pwd);
	}
	else if (path[1] && !check_stat_path(path[1]))
		error_path(path[1], &status);
	ft_free_arr(path);
	return (status);
}
