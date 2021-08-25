/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:03:47 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/24 13:38:25 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_ws(char *str)
{
	int	i;

	i = 0;
	while (ft_is_ws(str[i]))
		i++;
	return (i);
}

char	*add_char(t_data *data, char *str, int c)
{
	char	*new_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	new_str = malloc(len_str + 2);
	if (!new_str)
		exit_custom(data, NULL, AUTO);
	i = 0;
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free_null((void **)&str);
	return (new_str);
}

char	*concat_str(t_data *data, char *s1, char *s2)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (!new_str)
		exit_custom(data, NULL, AUTO);
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	free_null((void **)&s1);
	free_null((void **)&s2);
	return (new_str);
}
