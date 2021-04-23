/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:06:48 by fhamel            #+#    #+#             */
/*   Updated: 2020/01/20 15:07:04 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int		rest_mgmt(char **rest, char **line);
int		buff_mgmt(char **rest, char **line, char *buff);
int		get_next_line(int fd, char **line);
void	fill(char *dst, const char *src, char end);
int		concat(char **line, char *buff, char end);
int		only_eof(char **line);

#endif
