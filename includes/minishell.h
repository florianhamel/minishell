/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:02 by user42            #+#    #+#             */
/*   Updated: 2021/08/14 15:34:59 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "gnl.h"

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

/*
** parsing
*/
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

// exit flags
# define NOT_CUSTOM 0
# define CUSTOM 1

// redirection flags
# define SIMPLE_LEFT 1
# define DOUBLE_LEFT 2
# define SIMPLE_RIGHT 3
# define DOUBLE_RIGHT 4

// utils values
# define NOT_FOUND -1

typedef struct s_data
{
	char		**env;
	int			status;
	char		*str;
	t_history	*history;
	t_cmd		*cmd_lst;
}		t_data;


typedef struct s_history
{
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}		t_history;

typedef struct s_read
{
	int			c;
	size_t		pos;
	size_t		len;
	t_history	*current;
	char		*str;
	t_data		*data;
}		t_read;

typedef struct s_cmd
{
	char			*infile;
	char			*outfile;
	char			*cmd;
	char			*options;
	int				flag_in;
	int				flag_out;
	char			*word;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}		t_cmd;

// cmd_checkers.c
int		is_redir(int c);
int		is_quote(int c);
int		is_closed_quote();
int		is_special_char(int c);

// cmd_utils.c
int		skip_ws(char *str);
char	*add_char(char *str, int c);
char	*concat_str(char *s1, char *s2);
char	*get_file_cmd(t_data *data, int *pos);

// cmd.c
t_cmd	*new_elem_cmd(t_data *data);
void	append_cmd(t_cmd **cmd_lst, t_cmd *cmd);
t_cmd	*get_cmd_lst(t_data *data);
void	execute_cmd(t_data *data);

/*
** cursor_move.c
*/
void		cursor_right(int iter);
void		cursor_left(int iter);
void		cursor_move(t_read *data);

// free_exit_cmd.c
void	free_data(t_data *data);
void	exit_custom(t_data *data, char *serror, int flag);

/*
** free_exit_parsing.c
*/
void		free_null(void **ptr);
void		exit_strerror(void);
void		free_parsing(t_read *data);
void		exit_parsing(t_read *data);

/*
** history_navigation.c
*/
void		go_up(t_read *data);
void		go_down(t_read *data);
void		history_navigation(t_read *data);

/*
** history_utils.c
*/
t_history	*new_elem_history(char *line);
void		push_front(t_history *elem, t_history **history);
void		append_history(t_history **history, char *line);
void		free_history(t_history *elem);
void		fill_history(int fd, int max, t_history **history);

/*
** history_utils2.c
*/
void		replace_alloc(char *str, t_history *elem);
void		write_ws(size_t nb);
void		wipe_and_replace(t_read *data, t_history *elem);

/*
** history.c
*/
int			get_nb_lines(void);
int			go_to_line(int nb_lines, int max);
t_history	*get_list(int fd, int max);
void		flip_history(t_history **history);
t_history	*get_history(int max);

/*
** main.c
*/
void		intro(void);
void		minishell(void);

// quotes.c
// Uniquement pour data->word (double redir limiter)
char	*get_quote_word(t_data *data, int *pos);
char	*get_simple_quote(t_data *data, int *pos);
char	*get_double_quote(t_data *data, int *pos);
char	*get_quote(t_data *data, int *pos);

/*
** read_utils.c
*/
t_read		*init_read(t_history **history);
void		abort_cmd(t_read *data, int *status);
int			ft_getc(t_read *data);
int			get_last_char(t_read *data);

/*
** read.c
*/
void		eof_mgmt(t_read *data);
void		key_mgmt(t_read *data);
void		add_cmd(t_read *data, t_history **history);
t_read		*get_input(t_history **history, int *status);

// set_redir_utils.c
int		get_flag_in(t_data *data, int *pos);
int		get_flag_out(t_data *data, int *pos);
char	*get_word(t_data *data, int *pos);


// set_redir.c
void	redir_syntax_error(t_data *data, int *pos, t_cmd *cmd);
void	set_redir(t_data *data, int *pos, t_cmd *cmd);

/*
** str_utils.c
*/
char		*get_next(t_read *data);
char		*get_to_write(t_read *data);

/*
** str.c
*/
char		*new_del(t_read *data);
char		*new_insert(t_read *data);
char		*new_char(t_read *data);
void		str_mgmt(t_read *data);

/*
** utils_parsing.c
*/

char		**copy_env(void);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
void		ws_fd(size_t nb, int fd);
char		*new_alloc(char *str, size_t size, size_t pos);

// var.c
char	*get_var_name(t_data *data, int *pos);
char	*get_var_val(t_data *data, int *pos);

#endif