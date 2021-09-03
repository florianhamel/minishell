/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 22:22:20 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/03 15:48:54 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(t_data *data, t_redir *redir, int fd)
{
	char	*line;

	ft_putstr_fd("> ", STDIN_FILENO);
	if (get_next_line(STDIN_FILENO, &line) == ERROR)
		exit_custom(data, NULL, AUTO);
	while (ft_strncmp(redir->word, line, ft_strlen(redir->word) + 1))
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free_null((void **)&line);
		ft_putstr_fd("> ", STDIN_FILENO);
		if (get_next_line(STDIN_FILENO, &line) == ERROR)
			exit_custom(data, NULL, AUTO);
	}
	free_null((void **)&line);
}

int	get_heredoc(t_data *data, t_redir *redir)
{
	int		fd;

	fd = open(".heredoc", O_WRONLY | O_CREAT, 0666);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	write_heredoc(data, redir, fd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	if (unlink(".heredoc") == ERROR)
		exit_custom(data, NULL, AUTO);
	return (fd);
}

int	get_infile(t_data *data, t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->in_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_LEFT)
		{
			fd = open(current->word, O_RDONLY);
			if (fd == ERROR)
			{
				data->status = 1;
				exit_custom(data, ft_strdup(current->word), CUSTOM);
			}
		}
		else if (current->flag == DOUBLE_LEFT)
			fd = get_heredoc(data, current);
		current = current->next;
	}
	return (fd);
}

int	get_outfile(t_data *data, t_cmd *cmd)
{
	int		fd;
	t_redir	*current;

	fd = NO_FD;
	current = cmd->out_lst;
	while (current)
	{
		if (fd != NO_FD)
			close(fd);
		if (current->flag == SIMPLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (current->flag == DOUBLE_RIGHT)
			fd = open(current->word, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd == ERROR)
		{
			data->status = 2;
			exit_custom(data, current->word, CUSTOM);
		}
		current = current->next;
	}
	return (fd);
}

