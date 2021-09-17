/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:28:12 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/16 16:56:46 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_bad_path(int *status)
{
	ft_putstr_fd("minishell: cd: No such file or directory\n", \
	STDERR_FILENO);
	*status = 1;
}

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
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		status = 1;
	}
	else
	{
		if (!getcwd(ex_pwd, PATH_MAX_B))
			exit_custom(data, NULL, AUTO);
		if (chdir(path[1]) == ERROR)
			error_bad_path(&status);
		if (!getcwd(new_pwd, PATH_MAX_B))
			exit_custom(data, NULL, AUTO);
	}
	edit_env_value(data->var_lst, new_pwd, ex_pwd);
	ft_free_arr(path);
	return (status);
}
