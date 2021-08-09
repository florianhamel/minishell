/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/09 02:36:27 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history	*new_elem_history(char *line)
{
	t_history	*elem;

	elem = malloc(sizeof(t_history));
	if (!elem)
		ft_exit();
	elem->cmd = line;
	elem->next = NULL;
	elem->prev = NULL;
	return (elem);
}

void	append_cmd(t_history **history, char *line)
{
	t_history	*current;
	t_history	*new;

	if (!(*history))
		*history = new_elem_history(line);
	else
	{
		current = *history;
		while (current->prev)
			current = current->prev;
		new = new_elem_history(line);
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
	line = NULL;
	ret = get_next_line(fd, &line);
	i = 0;
	while (i < max && ret > 0)
	{
		if (line && line[0])
		{
			append_cmd(&history, line);
			i++;
		}
		else
			ft_free((void **)&line);
		ret = get_next_line(fd, &line);
	}
	if (line && line[0])
		append_cmd(&history, line);
	else
		ft_free((void **)&line);
	if (ret == ERROR)
		ft_exit();
	if (!history)
		history = new_elem_history(NULL);
	return (history);
}

void	flip_history(t_history **history)
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

	nb_lines = get_nb_lines();
	fd = go_to_line(nb_lines, max);
	if (fd < 0)
		ft_exit();
	history = get_list(fd, max);
	flip_history(&history);
	if (history->cmd)
		push_front(new_elem_history(NULL), &history);
	return (history);
}
