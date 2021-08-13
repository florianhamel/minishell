/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhamel <fhamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:01:35 by fhamel            #+#    #+#             */
/*   Updated: 2021/08/13 11:52:16 by fhamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "minishell.h"

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

typedef struct s_data
{
	char		**env;
	int			status;
	char		*str;
	t_history	*history;
	t_cmd		*cmd_lst;
}		t_data;

// cmd_checkers.c
int	is_redir(int c);
int	is_quote(int c);
int	is_special_char(int c);

// cmd_utils.c
char	*add_char(char *str, int c);
int		skip_ws(char *str);

// cmd.c
t_cmd	*new_elem_cmd(t_data *data);
void	append_cmd(t_cmd **cmd_lst, t_cmd *cmd);
t_cmd	*get_cmd_lst(t_data *data);
void	set_cmd(t_data *data, int *pos, t_cmd *cmd);
void	execute_cmd(t_data *data);

// free_exit_cmd.c
void	free_data(t_data *data);
void	exit_custom(t_data *data, char *serror, int flag);

// quotes.c
char	*get_quotation(t_data *data, int *pos);

// set_redir.c
void	redir_syntax_error(t_data *data, int *pos, t_cmd *cmd);
int		get_redir_flag(t_data *data, int *pos, t_cmd *cmd);
char	*get_redir_infile(t_data *data, int *pos, t_cmd *cmd);
char	*get_redir_outfile(t_data *data, int *pos, t_cmd *cmd);
void	set_redir(t_data *data, int *pos, t_cmd *cmd);

// var.c
char	*get_var_name(t_data *data, int *pos);
char	*get_var_val(t_data *data, int *pos);

#endif