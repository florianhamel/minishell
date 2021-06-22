/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/06/04 17:14:54 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_history	*new_history(char *line)
{
	t_history *elem;

	if (!(elem = malloc(sizeof(t_history))))
		ft_exit();
	elem->cmd = line;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void		append_cmd(t_history **history, char *line)
{
	t_history	*current;
	t_history	*new;

	if (!(*history))
		*history = new_history(line);
	else
	{
		current = *history;
		while (current->prev)
			current = current->prev;
		new = new_history(line);
		new->next = current;
		current->prev = new;
	}
}

t_history	*get_list(int fd, int max)
{
	t_history	*history;
	char		*line;
	int			ret;
	int			i;

	history = NULL;
	i = 0;
	while (i < max && (ret = get_next_line(fd, &line)) > 0)
	{
		if (line && line[0])
		{
			append_cmd(&history, line);
			i++;
		}
	}
	if (ret < 0)
		ft_exit();
	if (line && line[0])
		append_cmd(&history, line);
	return (history);
}

void		flip_history(t_history **history)
{
	t_history	*current;

	current = *history;
	while (current->prev)
		current = current->prev;
	*history = current;
}

t_history	*get_history(int max)
{
	t_history	*history;
	int			fd;
	int			nb_lines;

	if ((nb_lines = get_nb_lines()) < 0)
		ft_exit();
	if ((fd = go_to_line(nb_lines, max)) < 0)
		ft_exit();
	history = get_list(fd, max);
	if (history)
		flip_history(&history);
	return (history);
}
