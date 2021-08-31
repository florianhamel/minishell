/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 17:40:54 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/31 02:00:00 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	get_nb_words(const char *str, char sep)
{
	int	nb_words;
	int	i;

	nb_words = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
			nb_words++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (nb_words);
}

int	get_len_word(const char *str, char sep)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	return (i);
}

int	alloc_words(char **arr_words, const char *str, char sep)
{
	int		index;
	int		i;

	index = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
		{
			arr_words[index] = malloc(get_len_word(&str[i], sep) + 1);
			if (!arr_words[index])
			{
				arr_words[index] = NULL;
				ft_free_arr(arr_words);
				return (-1);
			}
			index++;
			while (str[i] && str[i] != sep)
				i++;
		}
	}
	return (0);
}

void	fill_words(char **arr_words, const char *str, char sep)
{
	int	index;
	int	i;
	int	j;

	index = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == sep)
			i++;
		if (str[i])
		{
			j = 0;
			while (str[i] && str[i] != sep)
				arr_words[index][j++] = str[i++];
			arr_words[index][j] = '\0';
			index++;
		}
	}
	arr_words[index] = NULL;
}

char	**ft_split(const char *str, char sep)
{
	char	**arr_words;

	if (!str)
		return (NULL);
	arr_words = malloc(sizeof(char *) * (get_nb_words(str, sep) + 1));
	if (!arr_words)
		return (NULL);
	if (alloc_words(arr_words, str, sep) == -1)
		return (NULL);
	fill_words(arr_words, str, sep);
	return (arr_words);
}
