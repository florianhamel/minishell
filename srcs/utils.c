/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/08 11:50:44 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_exit(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

void	free_parsing(t_read *data)
{
	free_history(data->current);
	ft_free((void **)&data->str);
	ft_free((void **)&data);
}

void	exit_parsing(t_read *data)
{
	free_parsing(data);
	ft_exit();
}

ssize_t	ft_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (ret);
	ret = write(fd, buf, nbyte);
	if (ret == ERROR)
		ft_exit();
	return (ret);
}

void	ws_fd(size_t nb, int fd)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_write(fd, " ", 1);
		i++;
	}
}

char	*new_alloc(char *str, size_t size, size_t pos)
{
	char	*new;
	size_t	i;

	i = 0;
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	new = (char *)ft_memcpy(new, str, pos);
	new[size] = '\0';
	ft_free((void **)&str);
	return (new);
}
