/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:45:56 by fhamel            #+#    #+#             */
/*   Updated: 2019/10/22 15:46:30 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int		check_empty(char const *s1, char const *set)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (!is_set(s1[i], set))
			return (0);
		i++;
	}
	return (1);
}

int		to_trim_start(char const *s1, char const *set)
{
	int	to_trim;
	int	index;

	to_trim = 0;
	index = 0;
	while (s1[index] && is_set(s1[index], set))
	{
		to_trim++;
		index++;
	}
	return (to_trim);
}

int		to_trim_end(char const *s1, char const *set)
{
	int	to_trim;
	int	index;

	to_trim = 0;
	index = ft_strlen(s1) - 1;
	while (index >= 0 && is_set(s1[index], set))
	{
		to_trim++;
		index--;
	}
	return (to_trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		end;
	int		index;
	int		i;

	if (!s1 || !set)
		return (NULL);
	if (check_empty(s1, set))
	{
		if (!(str = (char *)malloc(sizeof(char))))
			return (NULL);
		*str = '\0';
		return (str);
	}
	if (!(str = (char *)malloc(sizeof(char) *
	(ft_strlen(s1) - to_trim_start(s1, set) - to_trim_end(s1, set) + 1))))
		return (NULL);
	end = ft_strlen(s1) - to_trim_end(s1, set);
	index = to_trim_start(s1, set);
	i = 0;
	while (index < end)
		str[i++] = s1[index++];
	str[i] = '\0';
	return (str);
}
