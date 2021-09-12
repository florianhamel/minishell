/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Fayel-ha <Fayel-ha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 16:41:35 by Fayel-ha          #+#    #+#             */
/*   Updated: 2021/09/07 16:41:43 by Fayel-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, char **args)
{
	char	cwd[PATH_MAX];

	(void)data;
	(void)args;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (1);
	}
	else
	{
		perror("getcwd()");
		return (0);
	}
}
