/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:40:33 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/09 18:41:37 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (args[i + 1])
	{
		printf("Wrong Options\n");
		return (1);
	}
	while (data->env[i])
	{
		if (ft_strcmp(args[0], "export") == 0)
			printf("export ");
		printf("%s\n", data->env[i]);
		i++;
	}
	ft_free_arr(args);
	return (0);
}
