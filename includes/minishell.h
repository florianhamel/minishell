/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:28:02 by user42            #+#    #+#             */
/*   Updated: 2021/09/06 17:16:03 by fhamel           ###   ########.fr       */
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
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

# include "libft.h"
# include "gnl.h"

/*
** parsing
*/
# define NL_KEY 10
# define RIGHT_KEY 4414235
# define LEFT_KEY 4479771
# define UP_KEY 4283163
# define DOWN_KEY 4348699
# define PAGE_UP 4741915
# define PAGE_DOWN 4610843
# define DELETE 2117294875
# define CTRL_DEL 23
# define CTRL_S 19
# define EXIT_KEY 3
# define EOF_KEY -1
# define DEL_KEY 127
# define CTRL_C 3
# define CTRL_D 4

// exit flags
# define AUTO 0
# define CUSTOM 1

// redirection flags
# define SIMPLE_LEFT 1
# define DOUBLE_LEFT 2
# define SIMPLE_RIGHT 1
# define DOUBLE_RIGHT 2

// utils values
# define NO_FD -2
# define NOT_FOUND -1
# define ERROR -1
# define SUCCESS 0
# define CHILD 0
# define REDIR 1
# define PIPE 2

typedef struct s_history
{
	char				*cmd;
	struct s_history	*prev;
	struct s_history	*next;
}		t_history;

typedef struct s_read
{
	int					c;
	size_t				pos;
	size_t				len;
	struct s_history	*current;
	char				*str;
	struct s_data		*data;
}		t_read;

typedef struct s_var
{
	char			*name;
	char			*val;
	struct s_var	*prev;
	struct s_var	*next;
}		t_var;

typedef struct s_redir
{
	char			*word;
	int				flag;
	struct s_redir	*prev;
	struct s_redir	*next;
}		t_redir;

typedef struct s_cmd
{
	struct s_redir	*in_lst;
	struct s_redir	*out_lst;
	char			*args;
	t_var			*var_def_lst;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_data
{
	char				**env;
	char				*str;
	int					status;
	struct s_var		*var_lst;
	struct s_cmd		*cmd_lst;
	struct s_history	*history;
}		t_data;

typedef struct s_run
{
	int	fd[2];
	int	fd_pipe;
	int	fd_in;
	int	fd_out;
	int	status;
}		t_run;

typedef struct s_sig
{
	t_data	*data;
	int		pid;
}		t_sig;

// bin.c
char		*get_path_bin(t_data *data, char *name, char *var_path);
char		*get_bin(t_data *data, char *name);
char		**get_argv(t_data *data, t_cmd *cmd);

// bin_utils.c
int			check_slash_in(char *name);
int			is_direct_path(char *name);
char		*concat_path_bin(t_data *data, char *path, char *bin);
char		*get_var_path(t_data *data);

// call.c
void		dup2_close(int new_fd, int old_fd);
int			is_builtin(t_data *data, t_cmd *cmd);
void		call_setup(t_data *data, t_cmd *cmd, t_run run);
int			call_builtin(t_data *data, t_cmd *cmd, t_run run);
void		call_execve(t_data *data, t_cmd *cmd, t_run run);

// cmd_checkers.c
int			is_redir(int c);
int			is_quote(int c);
int			is_closed_quote(t_data *data, int *pos);
int			is_end_arg(int c);

// cmd_utils.c
int			skip_ws(char *str);
char		*add_char(t_data *data, char *str, int c);
char		*concat_str(t_data *data, char *s1, char *s2);

// cmd.c
char		*get_arg(t_data *data, int *pos);
t_cmd		*new_elem_cmd(t_data *data);
void		append_cmd(t_cmd **cmd_lst, t_cmd *cmd);
void		free_cmd_lst(t_data *data);
t_cmd		*get_cmd_lst(t_data *data);

// debug tool
void		print_cmd(t_data *data);

/*
** cursor_move.c
*/
void		cursor_right(int iter);
void		cursor_left(int iter);
void		cursor_move(t_read *data);

// free_exit_cmd.c
void		free_var_lst(t_var *var_lst);
void		free_data(t_data *data);
char		*custom_sterror(int status);
void		exit_custom(t_data *data, char *serror, int flag);

/*
** free_exit_parsing.c
*/
void		free_null(void **ptr);
void		exit_strerror(void);
void		free_parsing(t_read *data);
void		exit_parsing(t_read *data);

// heredoc_utils.c
void		stop_heredoc(t_read *heredoc);
void		eof_heredoc(t_read *heredoc, t_redir *redir);
void		input_heredoc(t_read *heredoc, t_redir *redir);

// heredoc.c
t_read		*init_heredoc(t_data *data);
void		write_heredoc(t_read *heredoc, t_redir *redir, int fd);
int			get_heredoc(t_data *data, t_redir *redir);

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

// minishell.c
void		intro(void);
t_data		*init_data(void);
void		minishell(void);

// open.c
int			get_infile(t_data *data, t_cmd *cmd);
int			get_outfile(t_data *data, t_cmd *cmd);

// quotes.c
char		*get_quote_word(t_data *data, int *pos);
char		*get_simple_quote(t_data *data, int *pos);
char		*get_double_quote(t_data *data, int *pos);
char		*get_quote(t_data *data, int *pos);

/*
** read_utils.c
*/
t_read		*init_read(t_data *data);
void		abort_cmd(t_read *data, int *status);
int			ft_getc(t_read *data);
int			get_last_char(t_read *data);

/*
** read.c
*/
void		eof_mgmt(t_read *data);
void		key_mgmt(t_read *data);
void		add_cmd(t_read *data, t_history **history);
t_read		*get_input(t_data *data);

// run.c
void		stop_process(int signum);
int			run_builtin(t_data *data, t_cmd *cmd, int fd_pipe);
int			run_execve(t_data *data, t_cmd *cmd, int fd_pipe);
void		run(t_data *data);

// set_utils.c
char		*get_word(t_data *data, int *pos);
int			get_flag_in(t_data *data, int *pos);
int			get_flag_out(t_data *data, int *pos);
void		set_redir_in(t_data *data, int *pos, t_cmd *cmd);
void		set_redir_out(t_data *data, int *pos, t_cmd *cmd);

// set.c
int			syntax_error(t_data *data, int flag);
int			check_syntax_error(t_data *data);
void		free_redir_lst(t_redir *redir);
void		set_redir(t_data *data, int *pos, t_cmd *cmd);
void		set_args(t_data *data, int *pos, t_cmd *cmd);

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
char		**copy_env(t_data *data);
t_var		*init_var_lst(t_data *data);
ssize_t		ft_write(int fd, const void *buf, size_t nbyte);
void		ws_fd(size_t nb, int fd);
char		*new_alloc(char *str, size_t size, size_t pos);

// var_def.c
void		add_var_def_lst(t_data *data, t_var *var_def_lst);
int			is_var_def(char *str);
char		*get_var_def_name(t_data *data, int *pos);
char		*get_var_def_val(t_data *data, int *pos);
void		set_var_def(t_data *data, int *pos, t_cmd *cmd);

// var_utils.c
int			find_var_env(t_data *data, char *var_name);
char		*search_env(t_data *data, char *var_name);
char		*search_var_lst(t_data *data, char *var_name);

// var.c
char		*get_var_name(t_data *data, int *pos);
char		*get_var_val(t_data *data, char *var_name);
char		*get_var(t_data *data, int *pos);

#endif