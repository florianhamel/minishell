/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 20:29:28 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/04 17:10:26 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	write_heredoc(t_data *data, t_redir *redir, int fd)
// {
// 	int		ret;
// 	char	*line;

// 	ft_putstr_fd("> ", STDIN_FILENO);
// 	ret = get_next_line(STDIN_FILENO, &line);
// 	if (ret == ERROR)		
// 		exit_custom(data, NULL, AUTO);
// 	else if (ret == 0 && !ft_strlen(line))
// 	{
// 		ft_putstr_fd("minishell: warning: EOF, wanted ('", STDERR_FILENO);
// 		ft_putstr_fd(redir->word, STDERR_FILENO);
// 		ft_putstr_fd("')\n", STDERR_FILENO);
// 		free_unlink();
// 		exit(0);
// 	}
// 	while (ft_strncmp(redir->word, line, ft_strlen(redir->word) + 1))
// 	{
// 		ft_putstr_fd(line, fd);
// 		ft_putchar_fd('\n', fd);
// 		free_null((void **)&line);
// 		ft_putstr_fd("> ", STDIN_FILENO);
// 		if (get_next_line(STDIN_FILENO, &line) == ERROR)
// 			exit_custom(data, NULL, AUTO);
// 	}
// 	free_null((void **)&line);
// }

// int	get_heredoc(t_data *data, t_redir *redir)
// {
// 	int		fd;

// 	fd = open(".heredoc", O_TRUNC | O_WRONLY | O_CREAT, 0666);
// 	if (!fd)
// 		exit_custom(data, NULL, AUTO);
// 	write_heredoc(data, redir, fd);
// 	close(fd);
// 	fd = open(".heredoc", O_RDONLY);
// 	if (!fd)
// 		exit_custom(data, NULL, AUTO);
// 	if (unlink(".heredoc") == ERROR)
// 		exit_custom(data, NULL, AUTO);
// 	return (fd);
// }

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
