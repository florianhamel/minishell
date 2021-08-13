/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/12 13:32:15 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(void)
{
	char	**env;
	int		i;

	i = 0;
	while (__environ[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		exit_strerror();
	i = 0;
	while (__environ[i])
	{
		env[i] = ft_strdup(__environ[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
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
	free_null((void **)&str);
	return (new);
}
