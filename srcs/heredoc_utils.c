/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 16:05:43 by fhamel            #+#    #+#             */
/*   Updated: 2021/09/06 15:28:11 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_heredoc(t_read *heredoc)
{
	free_history(heredoc->data->history);
	free_data(heredoc->data);
	free_null((void **)&heredoc->str);
	free_null((void **)&heredoc);
	ft_putstr_fd("^C\n", STDERR_FILENO);
	unlink(".heredoc");
	exit(130);
}

void	eof_heredoc(t_read *heredoc, t_redir *redir)
{
	if (!heredoc->str || heredoc->str[0])
	{
		ft_putstr_fd("minishell: warning: EOF, wanted ('", STDERR_FILENO);
		ft_putstr_fd(redir->word, STDERR_FILENO);
		ft_putstr_fd("')\n", STDERR_FILENO);
		free_history(heredoc->data->history);
		free_data(heredoc->data);
		free_null((void **)&heredoc->str);
		free_null((void **)&heredoc);
		unlink(".heredoc");
		exit(0);
	}
}

void	input_heredoc(t_read *heredoc, t_redir *redir)
{
	if (heredoc->c == CTRL_D)
		eof_heredoc(heredoc, redir);
	else if (heredoc->c == RIGHT_KEY || heredoc->c == LEFT_KEY)
		cursor_move(heredoc);
	else if (32 <= heredoc->c && heredoc->c <= 127)
		str_mgmt(heredoc);
}
