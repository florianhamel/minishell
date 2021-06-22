/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:16:40 by fhamel            #+#    #+#             */
/*   Updated: 2021/05/04 15:02:18 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		get_nb_lines(void)
{
	char	*line;
	int		fd;
	int		nb;
	int		ret;

	line = NULL;
	nb = 0;
	if ((fd = open("documents/.minishell_history",\
	O_CREAT | O_RDONLY, 0666)) < 0)
		ft_exit();
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		line = ft_free(line);
		nb++;
	}
	if (!line || (nb == 0 && line && line[0] == '\0'))
		return (nb);
	line = ft_free(line);
	if (close(fd) < 0 || ret < 0)
		ft_exit();
	return (nb + 1);
}

int			go_to_line(int nb_lines, int max)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	line = NULL;
	i = 0;
	if ((fd = open("documents/.minishell_history", O_RDONLY, 0666)) < 0)
		ft_exit();
	while (i < (nb_lines - max) && (ret = get_next_line(fd, &line)) > 0)
	{
		line = ft_free(line);
		i++;
	}
	line = ft_free(line);
	if (ret < 0)
		ft_exit();
	return (fd);
}

void	push_front(t_history *elem, t_history **history)
{
	(*history)->prev = elem;
	elem->next = *history;
	*history = elem;
}

void	replace_alloc(char *str, t_history *elem)
{
	ft_free(elem->cmd);
	if (!(elem->cmd = ft_strdup(str)))
		ft_exit();
}

void	write_ws(size_t nb)
{
	size_t	i;

	i = 0;
	while (i < nb)
	{
		ft_write(0, " ", 1);
		i++;
	}
}

void	wipe_and_replace(t_read *data, t_history *elem)
{
	size_t	wipe_len;
	size_t	replace_len;

	wipe_len = ft_strlen(data->str);
	cursor_left(data->pos);
	write_ws(wipe_len);
	cursor_left(wipe_len);
	ft_free(data->str);
	replace_len = ft_strlen(elem->cmd);
	if (elem->cmd)
		ft_write(0, elem->cmd, ft_strlen(elem->cmd));
	data->str = ft_strdup(elem->cmd);
	data->pos = replace_len;
	data->len = replace_len;
}

void	print_list(t_history *history)
{
	t_history	*current;

	current = history;
	while (current != NULL)
	{
		printf("%s\n", current->cmd);
		current = current->next;
	}
}