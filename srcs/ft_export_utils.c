/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fayel-ha <Fayel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 16:14:45 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/09 16:14:55 by Fayel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cpy_export(t_data *data, char *name, char *val)
{
	char	**tab2;
	char	*tmp1;
	int		j;

	j = 0;
	// JE NE FREE PAS TAB2 LEAKS
	while (data->env[j])
	{
		tab2 = ft_split(data->env[j], '=');
		if (strcmp(tab2[0], name) == 0)
		{
			tmp1 = ft_strjoin(name, "=");
			data->env[j] = ft_strjoin(tmp1, val);
			free(tmp1);
			return ;
		}
		j++;
	}
	ft_mallocb(data, val, name); // 2 mallocb sont appeler mais pourtant cela fonctionne et si j'enleve celui ci ca marche plus
}

int	split_tab(char **args, t_exp *tmp)
{
	tmp->tab = ft_split(args[tmp->i], '=');
	tmp->name = tmp->tab[0];
	tmp->val = tmp->tab[1];
	tmp->j = 0;
	return (1);
}

int	loop_exp(t_data *data, char **args, t_exp *tmp)
{
	while (data->env[tmp->j])
	{
		// pareil pour tab2 il n'est pas free
		tmp->tab2 = ft_split(data->env[tmp->j], '=');
		if (strcmp(tmp->tab2[0], tmp->tab[0]) == 0)
		{
			tmp->tmp1 = ft_strjoin(tmp->name, "=");
			data->env[tmp->j] = ft_strjoin(tmp->tmp1, tmp->val);
			free(tmp->tmp1);
			tmp->count = 1;
			if (args[tmp->i + 1] == NULL)
				return (0);
		}
		tmp->j++;
	}
	return (1);
}

int	ft_continue(t_data *data, char **args, t_exp *tmp)
{
	if (is_char(args[tmp->i], '=') == 0)
	{
		ft_add_env(data, tmp->tab);
		tmp->i++;
		return (1);
	}
	return (0);
}
