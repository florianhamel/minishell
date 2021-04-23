/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 14:05:58 by fhamel            #+#    #+#             */
/*   Updated: 2021/04/23 15:58:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int			get_nb_lines(void)
{
	char	*line;
	int		nb;
	int		ret;
	int		fd;

	line = NULL;
	nb = 0;
	ret = 0;
	if ((fd = open("documents/.minishell_history", O_CREAT | O_RDONLY)) < -1)
		return (ERROR);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		free(line);
		nb++;
	}
	free(line);
	if (close(fd) < 0 || ret < 0)
		return (ERROR);
	if (nb == 0 && line[0] == 0)
		return (nb);
	return (nb + 1);
}

int			go_to_line(int max, int nb_lines)
{
	char	*line;
	int		fd;
	int		ret;
	int		i;

	line = NULL;
	i = 0;
	if ((fd = open("documents/.minishell_history", O_CREAT | O_RDONLY)) < 0)
		return (fd);
	while ((ret = get_next_line(fd, &line) > 0) && i < (nb_lines - max))
	{
		free(line);
		i++;
	}
	free(line);
	if (ret < 0)
		return (ERROR);
	return (fd);
}

int			init_history(t_history **history, int fd)
{
	char	*line;
	int		ret;

	if (!(*history = malloc(sizeof(t_history))))
		return (ERROR);
	if ((ret = get_next_line(fd, &line)) <= 0)
		return (ret);
	free(line);
	(*history)->cmd = line;
	(*history)->prev = NULL;
	(*history)->next = NULL;
	return (1);
}

void		append_cmd(t_history **history, char *line)
{
	t_history	*current;

	current = (*history);
	// while (current->prev)
	return (current);
}

int			read_history(t_history **history, int max)
{
	char	*line;
	int		nb_lines;
	int		fd;
	int		i;

	i = 0;
	if ((nb_lines = get_nb_lines()) < 0)
		return (ERROR);
	if ((fd = go_to_line(max, nb_lines)) < 0)
		return (ERROR);
	while (get_next_line(fd, &line) > 0)
	{
		if (line)
			append_cmd(&history, line);
		free(line);
		i++;
	}
	free(line);
	return (0);
}

t_history	*get_history(int max)
{
	t_history	*history;
	int			ret;

	history = NULL;
	if ((ret = init_history(&history)) < 0)
		return (NULL);
	if (read_history(history, max) < 0)
		return (NULL);
	return (history);
}

char	*history_mgmt(void)
{
	t_history	*history;
	char		*str;

	history = get_history(20);
	return (NULL);
}