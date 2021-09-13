/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/13 12:48:02 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	intro(void)
{
	ft_putstr_fd("\033[0;37mminishell\033[0;92m$\033[0m ", 1);
}

ssize_t	ft_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (ret);
	ret = write(fd, buf, nbyte);
	if (ret == ERROR)
		exit_strerror();
	return (ret);
}

void	ws_fd(size_t nb, int fd)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_putchar_fd(' ', fd);
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
	free_null((void **)&str);
	return (new);
}
