/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:38:25 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/05 17:36:55 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <unistd.h>
# include <stdlib.h>

# define ERROR -1
# define EOF_READ 0
# define NO_NL 0
# define NL 1

int	get_len_line(char *line);
int	empty_line(char **line);
int	fill_line_nl(char **line);
int	fill_line(char **line, char *buf);
int	get_next_line(int fd, char **line);

#endif