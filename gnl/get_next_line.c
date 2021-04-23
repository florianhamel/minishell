/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:01:30 by fhamel            #+#    #+#             */
/*   Updated: 2020/01/20 15:05:41 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	rest_mgmt(char **rest, char **line)
{
	char	*new_rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(*rest) || (!(**rest)))
		return (0);
	while ((*rest)[i] != '\0' && (*rest)[i] != '\n')
		i++;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (-1);
	fill(*line, *rest, (*rest)[i]);
	if ((*rest)[i] == '\n')
	{
		while ((*rest)[j])
			j++;
		if (!(new_rest = (char *)malloc(sizeof(char) * (j + 1 - i))))
			return (-1);
		fill(new_rest, &(*rest)[i + 1], '\0');
		free(*rest);
		*rest = new_rest;
		return (1);
	}
	return (0);
}

int	buff_mgmt(char **rest, char **line, char *buff)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i] != '\0' && buff[i] != '\n')
		i++;
	if (concat(line, buff, buff[i]))
		return (-1);
	if (buff[i] == '\n')
	{
		while (buff[j])
			j++;
		free(*rest);
		if (!(*rest = (char *)malloc(sizeof(char) * (j - i))))
			return (-1);
		fill(*rest, &buff[i + 1], '\0');
		return (1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *rest = NULL;
	int			ret;
	int			b_read;
	char		buff[BUFFER_SIZE + 1];

	if (BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = NULL;
	if ((ret = rest_mgmt(&rest, line)))
		return (ret);
	while ((b_read = read(fd, buff, BUFFER_SIZE)))
	{
		if (b_read < 0)
			return (-1);
		buff[b_read] = '\0';
		if ((ret = buff_mgmt(&rest, line, buff)))
			return (ret);
	}
	if (only_eof(line))
		return (-1);
	free(rest);
	rest = NULL;
	return (0);
}
