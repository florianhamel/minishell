/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fayel-ha <Fayel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 12:36:28 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/07 18:49:56 by Fayel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_uns(char **args, int i)
{
	int	j;

	j = 0;
	while (args[i][j])
	{
		if (ft_isalpha(args[i][0]) == 0)
		{
			printf("Not a Valid Identifier\n");
			return (1);
		}
		if (!(ft_isalpha(args[i][j]) || ft_isdigit(args[i][j]) || \
		args[i][j] == '_'))
		{
			printf("Not a Valid Identifier\n");
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_unset(t_data *data, char **args, int i)
{
	t_var	*tmp;

	tmp = data->var_lst;
	if (ft_strncmp(args[0], "unset", 6) == 0 && args[1] == NULL)
		return (0);
	if (ft_error_uns(args, i))
		return (1);
	ft_unset_env(data, args, i);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, args[i]) == 0)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			ft_free_unset(tmp);
			i++;
			if (args[i])
				ft_unset(data, args, i);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_unset_env(t_data *data, char **args, int i)
{
	int	j;
	int	n;

	n = ft_strlen(args[i]);
	j = 0;
	while (data->env[j])
	{
		if (ft_strncmp(data->env[j], args[i], n) == 0)
		{
			while (data->env[j + 1])
			{
				data->env[j] = data->env[j + 1];
				j++;
			}
			data->env[j] = NULL;
			free(data->env[j + 1]);
			if (args[i + 1])
				ft_unset(data, args, i + 1);
			return (1);
		}
		j++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_free_unset(t_var *tmp)
{
	free(tmp->name);
	free(tmp->val);
	free(tmp);
}
