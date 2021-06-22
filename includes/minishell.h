/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:02 by user42            #+#    #+#             */
/*   Updated: 2021/06/04 17:20:44 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>

# define NL_KEY 10
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define EXIT_KEY 3
# define EOF_KEY -1
# define DEL_KEY 127
# define CTRL_C 3
# define CTRL_D 4
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
	int					status;
	size_t				pos;
	size_t				len;
	t_history			*current;
	char				*str;
}						t_read;

/*
** gnl
*/
int			get_next_line(int fd, char **line);

/*
** main.c
*/
void		intro(void);

/*
** utils.c
*/
void		*ft_free(void *ptr);
void		ft_exit(void);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
void		ws_fd(size_t nb, int fd);
char		*new_alloc(char *str, size_t size, size_t pos);

/*
** utils2.c
*/


/*
** read.c
*/
void		eof_mgmt(char *str);
void		key_mgmt(t_read *data);
void		add_cmd(t_read *data, t_history **history);
char		*get_cmd(t_history **history, int *status);

/*
** read_utils.c
*/
t_read		*init_data(t_history **history);
int			ft_getc(void);
int			get_last_char(void);

/*
** cursor_mgmt.c
*/
void		cursor_mgmt(t_read *data);
void		cursor_right(int iter);
void		cursor_left(int iter);

/*
** str.c
*/
char		*new_del(char *str, size_t pos);
char		*new_insert(char *str, size_t pos, int c);
char		*new_char(char *str, size_t size, int c);
void		str_mgmt(t_read *data);

/*
** str_utils.c
*/
char		*get_next(char *str, size_t pos);
char		*get_to_write(char *str, size_t pos, int c);

/*
** history.c
*/
t_history	*new_history(char *line);
void		append_cmd(t_history **history, char *line);
t_history	*get_list(int fd, int max);
void		flip_history(t_history **history);
t_history	*get_history(int max);

/*
** history_mgmt.c
*/
void		go_up(t_read *data);
void		go_down(t_read *data);
void		history_mgmt(t_read *data);

/*
** history_utils.c
*/
int			get_nb_lines(void);
int			go_to_line(int nb_lines, int max);
void		push_front(t_history *elem, t_history **history);
void		replace_alloc(char *str, t_history *elem);
void		write_ws(size_t nb);
void		wipe_and_replace(t_read *data, t_history *elem);
void		print_list(t_history *history);

#endif