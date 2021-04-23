/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:02 by user42            #+#    #+#             */
/*   Updated: 2021/04/23 15:59:51 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# define NL_KEY 10
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define EXIT_KEY 3
# define EOF_KEY -1
# define DEL_KEY 127
# define ERROR -1

typedef	struct			s_history
{
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}						t_history;

typedef struct			s_read
{
	int					c;
	size_t				pos;
	size_t				len;
	char				*str;
	t_history			*history;
}						t_read;

/*
** gnl
*/
int		get_next_line(int fd, char **line);

/*
** main.c
*/
void	intro(void);
char	*get_cmd(void);
int		main(void);

/*
** utils.c
*/
void	ws_fd(size_t nb, int fd);
int		is_writable(int c);
char	*new_alloc(char *str, size_t size, size_t pos);

/*
** read.c
*/
char	*history_mgmt(void);
char	*key_mgmt(t_read *data);
char	*read_mgmt(void);

/*
** read_utils.c
*/
t_read	*init_data(void);
int		ft_getc(void);
int		get_last_char(void);

/*
** cursor.c
*/
void	cursor_mgmt(t_read *data);
void	cursor_right(int iter);
void	cursor_left(int iter);

/*
** str.c
*/
char	*new_del(char *str, size_t pos);
char	*new_insert(char *str, size_t pos, int c);
char	*new_char(char *str, size_t size, int c);
char	*str_mgmt(t_read *data);

/*
** str_utils.c
*/
char	*get_next(char *str, size_t pos);
char	*get_to_write(char *str, size_t pos, int c);

/*
** history.c
*/
int		get_nb_lines(void);


#endif