/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:03:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/06/03 14:55:13 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void		*ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
	return(NULL);
}

void		ft_exit(void)
{
	printf("%s\n", strerror(errno));
	exit(errno);
}

ssize_t		ft_write(int fd, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = 0;
	if (!buf)
		return (ret);
	if ((ret = write(fd, buf, nbyte)) < 0)
		ft_exit();
	return (ret);
}

void		ws_fd(size_t nb, int fd)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_write(fd, " ", 1);
		i++;
	}
}

char		*new_alloc(char *str, size_t size, size_t pos)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!(new = malloc(size + 1)))
		return (NULL);
	new = (char *)ft_memcpy(new, str, pos);
	new[size] = '\0';
	str = ft_free(str);
	return (new);
}
