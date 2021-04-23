/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 13:30:54 by fhamel            #+#    #+#             */
/*   Updated: 2021/04/22 13:31:31 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*get_next(char *str, size_t pos)
{
	char	*next;
	int		i;

	i = 0;
	if (!(next = malloc(ft_strlen(str) - pos + 1)))
		return (NULL);
	while (str[pos])
	{
		next[i] = str[pos];
		pos++;
		i++;
	}
	next[i] = '\0';
	return (next);
}

char	*get_to_write(char *str, size_t pos, int c)
{
	char	*to_write;
	int				i;

	i = 1;
	if (!(to_write = malloc(ft_strlen(str) - pos + 2)))
		return (NULL);
	to_write[0] = (char)c;
	while (str[pos])
	{
		to_write[i] = str[pos];
		pos++;
		i++;
	}
	to_write[i] = '\0';
	return (to_write);
}
