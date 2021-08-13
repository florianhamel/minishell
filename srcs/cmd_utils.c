/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:03:47 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/12 00:22:21 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

char	*add_char(char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free_null((void **)&str);
	return (new_str);
}

int	skip_ws(char *str)
{
	int	i;

	i = 0;
	while (ft_is_ws(str[i]))
		i++;
	return (i);
}
