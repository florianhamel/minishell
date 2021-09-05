/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:29:28 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/05 23:49:46 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_read	*init_heredoc(t_data *data)
{
	t_read	*data_parsing;

	data_parsing = malloc(sizeof(t_read));
	data_parsing->c = 0;
	data_parsing->pos = 0;
	data_parsing->len = 0;
	data_parsing->current = NULL;
	data_parsing->str = NULL;
	data_parsing->data = data;
	return (data_parsing);
}

void	write_heredoc(t_read *heredoc, t_redir *redir, int fd)
{
	while (ft_strncmp(redir->word, heredoc->str, \
	ft_strlen(redir->word) + 1))
	{
		heredoc->c = 0;
		heredoc->pos = 0;
		heredoc->len = 0;
		free_null((void **)&heredoc->str);
		ft_putstr_fd("> ", STDIN_FILENO);
		while (heredoc->c != NL_KEY)
		{
			heredoc->c = get_last_char(heredoc);
			if (heredoc->c == CTRL_C)
				stop_heredoc(heredoc);
			input_heredoc(heredoc, redir);
		}
		ft_putchar_fd('\n', STDIN_FILENO);
		if (!ft_strncmp(redir->word, heredoc->str, \
		ft_strlen(redir->word) + 1))
			break ;
		ft_putstr_fd(heredoc->str, fd);
		ft_putchar_fd('\n', fd);
	}
	free_null((void **)&heredoc->str);
}

int	get_heredoc(t_data *data, t_redir *redir)
{
	int		fd;
	t_read	*heredoc;

	fd = open(".heredoc", O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	heredoc = init_heredoc(data);
	write_heredoc(heredoc, redir, fd);
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (!fd)
		exit_custom(data, NULL, AUTO);
	unlink(".heredoc");
	return (fd);
}
