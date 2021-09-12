/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:59:05 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/09 18:23:48 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char **args)
{
	int	i;

	i = 0;
	if (args[1][0] == '-')
	{
		printf("Wrong Options\n");
		return (1);
	}
	return (0);
}

int	ft_export(t_data *data, char **args)
{
	t_exp	tmp;

	tmp.i = 1;
	if (ft_strncmp(args[0], "export", 7) == 0 && args[1] == NULL)
	{
		ft_env(data, args);
		return (0);
	}
	if (ft_error(args))
		return (1);
	while (args[tmp.i] && split_tab(args, &tmp))
	{
		tmp.count = 0;
		if (tmp.val == NULL)
			tmp.val = ft_strdup("");
		if (ft_continue(data, args, &tmp))
			continue ;
		if (data->env[tmp.j])
			if (loop_exp(data, args, &tmp) == 0)
				return (0);
		if (tmp.count == 0)
			ft_mallocb(data, tmp.val, tmp.name);
		tmp.i++;
	}
	return (0);
}

int	is_char(const char *s, char c)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == c)
			return (1);
		i--;
	}
	return (0);
}

void	ft_mallocb(t_data *data, char *val, char *name)
{
	char	**new;
	char	*tmp1;
	int		i;

	i = 0;
	while (data->env[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (data->env[i])
	{
		new[i] = ft_strdup(data->env[i]);
		free(data->env[i]);
		i++;
	}
	tmp1 = ft_strjoin(name, "=");
	new[i] = ft_strjoin(tmp1, val);
	free(tmp1);
	new[i + 1] = NULL;
	free(data->env);
	data->env = new;
}

void	ft_add_env(t_data *data, char **tab)
{
	t_var	*tmp;

	tmp = data->var_lst;
	while (tmp)
	{
		if (strcmp(tab[0], tmp->name) == 0)
			ft_cpy_export(data, tmp->name, tmp->val);
		tmp = tmp->next;
	}
}
