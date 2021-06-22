# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/25 20:20:38 by florianhame       #+#    #+#              #
#    Updated: 2021/06/08 15:41:14 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#####                              FILES VARS                              #####
################################################################################

MINISHELL	=	minishell

D_INCLUDES	=	includes/

D_OBJS		=	objs/

D_SRCS		=	srcs/

_SRC_		=	main.c \
				utils.c \
				utils2.c \
				read.c \
				read_utils.c \
				cursor_mgmt.c \
				str.c \
				str_utils.c \
				history.c \
				history_mgmt.c \
				history_utils.c

SRCS		=	$(addprefix $(D_SRCS), $(_SRC_))

OBJS		=	$(addprefix $(D_OBJS), $(_SRC_:.c=.o))

D_GNL		=	gnl/

GNL_SRC_	=	get_next_line.c \
				get_next_line_utils.c

GNL_OBJS	=	$(addprefix $(D_GNL), $(GNL_SRC_:.c=.o))

D_LIBFT		=	libft/

LIBFT		=	libft.a

OBJS		+=	$(GNL_OBJS)

################################################################################
#####                           COMPILER OPTIONS                           #####
################################################################################

CC			=	clang

FLAGS		=	-Wall -Wextra -Werror

FSANITIZE	=	-g -fsanitize=address

################################################################################
#####                            MAKEFILE RULES                            #####
################################################################################

all	: $(D_OBJS) $(LIBFT) $(MINISHELL)

$(D_OBJS) :
	mkdir -p $@

$(LIBFT) :
	@make -C $(D_LIBFT)

$(D_GNL)%.o : $(D_GNL)%.c
	$(CC) $(FLAGS) -c $< -o $@ -Ignl

$(D_OBJS)%.o : $(D_SRCS)%.c
	$(CC) $(FLAGS) -c $< -o $@ -Iincludes -Ilibft/includes

$(MINISHELL) : $(GNL_OBJS) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L$(D_LIBFT) -lft -o $@

clean :
	rm -rf $(D_OBJS)
	rm -rf $(GNL_OBJS)
	make clean -C $(D_LIBFT)

fclean : clean
	rm -rf $(MINISHELL)
	rm -rf $(D_LIBFT)$(LIBFT)

re : fclean all
